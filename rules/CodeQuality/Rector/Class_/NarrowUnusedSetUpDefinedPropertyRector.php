<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Name;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Property;
use PhpParser\NodeFinder;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Rector\ValueObject\MethodName;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\NarrowUnusedSetUpDefinedPropertyRectorTest
 */
final class NarrowUnusedSetUpDefinedPropertyRector extends AbstractRector
{
    /**
     * @var string
     */
    private const MOCK_OBJECT_CLASS = 'PHPUnit\Framework\MockObject\MockObject';

    private readonly NodeFinder $nodeFinder;

    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
    ) {
        $this->nodeFinder = new NodeFinder();
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Turn property used only in setUp() to variable', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
    private $someServiceMock;

    public function setUp(): void
    {
        $this->someServiceMock = $this->createMock(SomeService::class);
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
    public function setUp(): void
    {
        $someServiceMock = $this->createMock(SomeService::class);
    }
}
CODE_SAMPLE
                ,
            ),
        ]);
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

        $setUpClassMethod = $node->getMethod(MethodName::SET_UP);
        if (! $setUpClassMethod instanceof ClassMethod) {
            return null;
        }

        $hasChanged = false;

        foreach ($node->stmts as $key => $classStmt) {
            if (! $classStmt instanceof Property) {
                continue;
            }

            $property = $classStmt;
            if (! $property->type instanceof Name) {
                continue;
            }

            if (! $this->isName($property->type, self::MOCK_OBJECT_CLASS)) {
                continue;
            }

            if (! $this->isPropertyUsedOutsideSetUpClassMethod($node, $setUpClassMethod, $property)) {
                continue;
            }

            $hasChanged = true;

            unset($node->stmts[$key]);
            $propertyName = $property->props[0]->name->toString();

            // change property to variable in setUp() method
            $this->traverseNodesWithCallable($setUpClassMethod, function (Node $node) use (
                $propertyName
            ): ?Variable {
                if (! $node instanceof PropertyFetch) {
                    return null;
                }

                if (! $this->isName($node->var, 'this')) {
                    return null;
                }

                if (! $this->isName($node->name, $propertyName)) {
                    return null;
                }

                return new Variable($propertyName);
            });
        }

        if ($hasChanged) {
            return $node;
        }

        return null;
    }

    private function isPropertyUsedOutsideSetUpClassMethod(
        Class_ $class,
        ClassMethod $setUpClassMethod,
        Property $property
    ): bool {
        $isPropertyUsed = false;

        foreach ($class->getMethods() as $classMethod) {
            // skip setUp() method
            if ($classMethod === $setUpClassMethod) {
                continue;
            }

            // check if property is used anywhere else than setup
            $usedPropertyFetch = $this->nodeFinder->findFirst($classMethod, function (Node $node) use (
                $property
            ): bool {
                if (! $node instanceof PropertyFetch) {
                    return false;
                }

                if (! $this->isName($node->var, 'this')) {
                    return false;
                }

                $propertyName = $property->props[0]->name->toString();
                return $this->isName($node->name, $propertyName);
            });

            if ($usedPropertyFetch instanceof PropertyFetch) {
                $isPropertyUsed = true;
            }
        }

        return $isPropertyUsed;
    }
}
