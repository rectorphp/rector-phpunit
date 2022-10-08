<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Property;

use PhpParser\Comment\Doc;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\Namespace_;
use PhpParser\Node\Stmt\Property;
use PhpParser\Node\Stmt\Use_;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

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
    private $test;

    public function setUp(): void
    {
        $this->test = $this->prophesize(SomeClass::class);
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
    private $test;

    public function setUp(): void
    {
        $this->test = $this->prophesize(SomeClass::class);
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        // PhpParser\Node\Expr\Assign
        // PhpParser\Node\Expr\MethodCall
        return [Assign::class];
    }

    public function refactor(\PhpParser\Node $node)
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if (! $node instanceof Assign) {
            return;
        }

        $expr = $node->expr;

        if (! $expr instanceof MethodCall) {
            return;
        }

        $var = $expr->var;
        if (! $var instanceof Variable) {
            return;
        }

        if ($var->name !== 'this') {
            return;
        }

        $name = $expr->name;
        if (! $name instanceof Identifier) {
            return;
        }

        if ($name->name !== 'prophesize') {
            return;
        }

        $value = $expr->args[0]->value;

        if ($value instanceof String_) {
            $prophesizeClassParts = \explode('\\', $value->value);
        } elseif ($value instanceof ClassConstFetch) {
            $prophesizeClassParts = $value->class->parts;
        } else {
            return;
        }

        $var = $node->var;

        if (! $var instanceof PropertyFetch) {
            return;
        }

        $propertyName = $var->name->name;

        $class = $this->betterNodeFinder->findParentType($node, Class_::class);

        foreach ($class->stmts as $stmt) {
            if (! $stmt instanceof Property) {
                continue;
            }

            if ($stmt->props[0]->name->name !== $propertyName) {
                continue;
            }

            $doc = new Doc("/**\n     * @var ObjectProphecy<" . $prophesizeClassParts[array_key_last(
                $prophesizeClassParts
            )] . ">\n     */");
            $stmt->setDocComment($doc);
            $stmt->getDocComment();

            $useStatements = ['Prophecy\Prophecy\ObjectProphecy', \implode('\\', $prophesizeClassParts)];

            $namespace = $this->betterNodeFinder->findParentType($node, Namespace_::class);

            if (! $namespace instanceof Namespace_) {
                return;
            }

            foreach ($namespace->stmts as $stmt) {
                if (! $stmt instanceof Use_) {
                    continue;
                }

                $foundClass = \implode('\\', $stmt->uses[0]->name->parts);

                $findIndex = \array_search($foundClass, $useStatements, true);
                if ($findIndex !== false) {
                    unset($useStatements[$findIndex]);
                }
            }

            $uses = $this->nodeFactory->createUsesFromNames($useStatements);
            $stmts = $namespace->stmts;

            foreach ($uses as $use) {
                $stmts[] = $use; // TODO not working currently
            }

            $namespace->stmts = $stmts;

            break;
        }
    }
}
