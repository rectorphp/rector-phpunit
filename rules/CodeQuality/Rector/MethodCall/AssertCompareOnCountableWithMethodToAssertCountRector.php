<?php

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use Countable;
use PhpParser\Node;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\AssertCompareOnCountableWithMethodToAssertCountRectorTest
 */
class AssertCompareOnCountableWithMethodToAssertCountRector extends AbstractRector
{
    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('', [
            new CodeSample(<<<'CODE_SAMPLE'
$this->assertSame(1, $countable->count());
CODE_SAMPLE
,
            <<<'CODE_SAMPLE'
$this->assertCount(1, $countable);
CODE_SAMPLE
            )
        ]);
    }

    /**
     * @return array<class-string<Node\Expr\MethodCall>>
     */
    public function getNodeTypes(): array
    {
        return [Node\Expr\MethodCall::class, Node\Expr\StaticCall::class];
    }

    /**
     * @param Node\Expr\MethodCall|Node\Expr\StaticCall $node
     * @throws \PHPStan\ShouldNotHappenException
     */
    public function refactor(Node $node)
    {
        $class = $node instanceof Node\Expr\StaticCall ? $node->class : $node->var;

        if ($this->getType($class)->isSuperTypeOf(new ObjectType('PHPUnit\Framework\TestCase'))->no()) {
            return null;
        }

        if (!$node->name instanceof Node\Identifier || $node->name->toLowerString() !== 'assertsame') {
            return null;
        }

        $right = $node->getArgs()[1]->value;

        if (
            ($right instanceof Node\Expr\MethodCall)
            && $right->name instanceof Node\Identifier
            && $right->name->toLowerString() === 'count'
            && count($right->getArgs()) === 0
        ) {
            $type = $this->getType($right->var);

            if ((new ObjectType(Countable::class))->isSuperTypeOf($type)->yes()) {
                $args = $node->getArgs();
                $args[1] = $right->var;

                if ($node instanceof Node\Expr\MethodCall) {
                    return $this->nodeFactory->createMethodCall($node->var, 'assertCount', $args);
                }

                if ($node instanceof Node\Expr\StaticCall && $node->class instanceof Node\Name) {
                    return $this->nodeFactory->createStaticCall($node->class->toString(), 'assertCount', $args);
                }
            }
        }

        return null;
    }
}
