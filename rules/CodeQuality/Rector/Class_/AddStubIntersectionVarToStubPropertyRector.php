<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Property;
use PHPStan\PhpDocParser\Ast\PhpDoc\VarTagValueNode;
use PHPStan\PhpDocParser\Ast\Type\IdentifierTypeNode;
use PHPStan\PhpDocParser\Ast\Type\IntersectionTypeNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTypeChanger;
use Rector\BetterPhpDocParser\ValueObject\Type\BracketsAwareIntersectionTypeNode;
use Rector\PHPUnit\CodeQuality\NodeAnalyser\MockObjectPropertyDetector;
use Rector\PHPUnit\Enum\PHPUnitClassName;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Rector\ValueObject\MethodName;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\AddStubIntersectionVarToStubPropertyRectorTest
 */
final class AddStubIntersectionVarToStubPropertyRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly MockObjectPropertyDetector $mockObjectPropertyDetector,
        private readonly PhpDocInfoFactory $phpDocInfoFactory,
        private readonly PhpDocTypeChanger $phpDocTypeChanger,
    ) {
    }

    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Class_
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $setUpClassMethod = $node->getMethod(MethodName::SET_UP);
        if (! $setUpClassMethod instanceof ClassMethod) {
            return null;
        }

        $propertyNamesToCreateStubMethodCalls = $this->mockObjectPropertyDetector->collectFromClassMethod(
            $setUpClassMethod,
            'createStub'
        );
        if ($propertyNamesToCreateStubMethodCalls === []) {
            return null;
        }

        $hasChanged = false;

        foreach ($propertyNamesToCreateStubMethodCalls as $propertyName => $createStubMethodCall) {
            $property = $node->getProperty($propertyName);
            if (! $property instanceof Property) {
                continue;
            }

            // only properties typed as a bare native Stub
            if (! $this->mockObjectPropertyDetector->detect($property, PHPUnitClassName::STUB)) {
                continue;
            }

            $stubbedClass = $this->resolveStubbedClass($createStubMethodCall);
            if ($stubbedClass === null) {
                continue;
            }

            $intersectionTypeNode = new BracketsAwareIntersectionTypeNode([
                new IdentifierTypeNode('\\' . PHPUnitClassName::STUB),
                new IdentifierTypeNode('\\' . $stubbedClass),
            ]);

            $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($property);

            // already has an intersection @var, skip
            $varTagValueNode = $phpDocInfo->getVarTagValueNode();
            if ($varTagValueNode instanceof VarTagValueNode && $varTagValueNode->type instanceof IntersectionTypeNode) {
                continue;
            }

            $this->phpDocTypeChanger->changeVarTypeNode($property, $phpDocInfo, $intersectionTypeNode);

            $hasChanged = true;
        }

        if (! $hasChanged) {
            return null;
        }

        return $node;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add a Stub intersection @var docblock with the stubbed class to a native Stub property',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\Stub $someServiceStub;

    protected function setUp(): void
    {
        $this->someServiceStub = $this->createStub(SomeService::class);
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @var \PHPUnit\Framework\MockObject\Stub&\SomeService
     */
    private \PHPUnit\Framework\MockObject\Stub $someServiceStub;

    protected function setUp(): void
    {
        $this->someServiceStub = $this->createStub(SomeService::class);
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    private function resolveStubbedClass(MethodCall|StaticCall $createStubCall): ?string
    {
        $firstArg = $createStubCall->getArgs()[0] ?? null;
        if ($firstArg === null) {
            return null;
        }

        if (! $firstArg->value instanceof ClassConstFetch) {
            return null;
        }

        $className = $this->getName($firstArg->value->class);
        if (! is_string($className)) {
            return null;
        }

        return $className;
    }
}
