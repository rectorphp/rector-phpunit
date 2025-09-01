<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddParamTypeFromDependsRector\AddParamTypeFromDependsRectorTest
 */
final class AddParamTypeFromDependsRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly PhpDocInfoFactory $phpDocInfoFactory,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add param type declaration based on @depends test method return type',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        return new \stdClass();
    }

    /**
     * @depends test
     */
    public function testAnother($someObject)
    {
    }
}
CODE_SAMPLE

                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        return new \stdClass();
    }

    /**
     * @depends test
     */
    public function testAnother(\stdClass $someObject)
    {
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $hasChanged = false;

        foreach ($node->getMethods() as $classMethod) {
            if (! $classMethod->isPublic()) {
                continue;
            }

            if (count($classMethod->params) !== 1) {
                continue;
            }

            $soleParam = $classMethod->getParams()[0];

            // already known type
            if ($soleParam->type instanceof Node) {
                continue;
            }

            $dependsReturnType = $this->resolveReturnTypeOfDependsMethod($classMethod, $node);
            if (! $dependsReturnType instanceof Node) {
                continue;
            }

            $soleParam->type = $dependsReturnType;
            $hasChanged = true;
        }

        if ($hasChanged === false) {
            return null;
        }

        return $node;
    }

    private function resolveReturnTypeOfDependsMethod(ClassMethod $classMethod, Class_ $class): ?Node
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($classMethod);
        if (! $phpDocInfo instanceof PhpDocInfo) {
            return null;
        }

        $dependsTagValueNode = $phpDocInfo->getByName('depends');
        if (! $dependsTagValueNode instanceof PhpDocTagNode) {
            return null;
        }

        $dependsMethodName = (string) $dependsTagValueNode->value;
        $dependsMethodName = trim($dependsMethodName, '()');

        $dependsClassMethod = $class->getMethod($dependsMethodName);

        if (! $dependsClassMethod instanceof ClassMethod) {
            return null;
        }

        // resolve return type here
        return $dependsClassMethod->returnType;
    }
}
