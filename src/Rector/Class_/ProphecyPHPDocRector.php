<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Comment\Doc;
use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\Property;
use Rector\Core\NodeManipulator\ClassMethodPropertyFetchManipulator;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\ProphecyPHPDocRector\ProphecyPHPDocRectorTest
 */
class ProphecyPHPDocRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private ClassMethodPropertyFetchManipulator $classMethodPropertyFetchManipulator
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add correct @var to ObjectProphecy instances based on $this->prophesize() call.',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
class HelloTest extends TestCase
{
    /**
     * @var SomeClass
     */
    private $propesizedObject;

    public function setUp(): void
    {
        $this->propesizedObject = $this->prophesize(SomeClass::class);
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
class HelloTest extends TestCase
{
    /**
     * @var ObjectProphecy<SomeClass>
     */
    private $propesizedObject;

    public function setUp(): void
    {
        $this->propesizedObject = $this->prophesize(SomeClass::class);
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<\PhpParser\Node>>
     */
    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): Class_|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $hasChanged = false;

        foreach ($node->getProperties() as $property) {
            $propertyName = $this->getName($property);

            $toPropertyAssignExprs = $this->findAssignToPropertyName($node, $propertyName);

            foreach ($toPropertyAssignExprs as $toPropertyAssignExpr) {
                $prophesizedObjectArg = $this->matchThisProphesizeMethodCallFirstArg($toPropertyAssignExpr);
                if (! $prophesizedObjectArg instanceof Arg) {
                    continue;
                }

                $value = $prophesizedObjectArg->value;
                if ($value instanceof String_) {
                    $prophesizeClass = $value->value;
                } elseif ($value instanceof ClassConstFetch) {
                    $prophesizeClass = $value->class;
                } else {
                    continue;
                }
                //
                //                $var = $node->var;
                //                if (! $var instanceof PropertyFetch) {
                //                    continue;
                //                }

                $this->changePropertyDoc($property, $prophesizeClass);

                $hasChanged = true;
                break;
            }
        }

        if ($hasChanged) {
            return $node;
        }

        return null;
    }

    private function matchThisProphesizeMethodCallFirstArg(Expr $expr): ?Arg
    {
        //        if (! $expr->expr instanceof MethodCall) {
        //            return null;
        //        }

        $var = $expr->var;
        if (! $var instanceof Variable) {
            return null;
        }

        if (! $this->isName($var, 'this')) {
            return null;
        }

        //        if (! $assign->var instanceof PropertyFetch) {
        //            return null;
        //        }

        if (! $this->isName($expr->name, 'prophesize')) {
            return null;
        }

        return $expr->getArgs()[0];
    }

    /**
     * @return Expr[]
     */
    private function findAssignToPropertyName(Class_ $class, string $propertyName): array
    {
        $assignExprs = [];

        foreach ($class->getMethods() as $classMethod) {
            $currentAssignExprs = $this->classMethodPropertyFetchManipulator->findAssignsToPropertyName(
                $classMethod,
                $propertyName
            );
            $assignExprs = array_merge($assignExprs, $currentAssignExprs);
        }

        return $assignExprs;
    }

    private function changePropertyDoc(Property $property, string|Node\Name\FullyQualified $prophesizeClass): void
    {
        $doc = new Doc(
            \sprintf(
                "/**\n     * @var %s<%s>\n     */",
                '\Prophecy\Prophecy\ObjectProphecy',
                '\\' . $prophesizeClass,
            )
        );

        $property->setDocComment($doc);
    }
}
