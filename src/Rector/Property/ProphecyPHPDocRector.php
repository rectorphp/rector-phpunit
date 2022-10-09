<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Property;

use PhpParser\Comment\Doc;
use PhpParser\Node;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt\Class_;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRector\ProphecyPHPDocRectorTest
 */
class ProphecyPHPDocRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
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
        return [Assign::class];
    }

    /**
     * @param Assign $node
     */
    public function refactor(Node $node): Assign|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if (! $node instanceof Assign) {
            return null;
        }

        $expr = $node->expr;
        if (! $expr instanceof MethodCall) {
            return null;
        }

        $var = $expr->var;
        if (! $var instanceof Variable) {
            return null;
        }

        if (! $this->isName($var, 'this')) {
            return null;
        }

        if (! $this->isName($expr->name, 'prophesize')) {
            return null;
        }

        $value = $expr->args[0]->value;
        if ($value instanceof String_) {
            $prophesizeClassParts = \explode('\\', $value->value);
        } elseif ($value instanceof ClassConstFetch) {
            $prophesizeClassParts = $value->class->parts;
        } else {
            return null;
        }

        $var = $node->var;

        if (! $var instanceof PropertyFetch) {
            return null;
        }

        $propertyName = $var->name->name;
        $class = $this->betterNodeFinder->findParentType($node, Class_::class);
        if (! $class instanceof Class_) {
            return null;
        }

        foreach ($class->getProperties() as $property) {
            if (! $this->isName($property, $propertyName)) {
                continue;
            }

            $doc = new Doc(
                \sprintf(
                    "/**\n     * @var %s<%s>\n     */",
                    '\Prophecy\Prophecy\ObjectProphecy',
                    '\\' . \implode('\\', $prophesizeClassParts),
                )
            );

            $property->setDocComment($doc);
            $property->getDocComment();

            break;
        }

        return $node;
    }
}
