<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\FuncCall;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertClassnameComparisonToInstanceOfRector\AssertClassnameComparisonToInstanceOfRectorTest
 */
final class AssertClassNameComparisonToInstanceOfRector extends AbstractRector
{
    public function __construct(private readonly TestsNodeAnalyzer $testsNodeAnalyzer)
    {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns class name comparisons to their method name alternatives in PHPUnit TestCase',
            [
                new CodeSample(
                    '$this->assertNotEquals(SomeInstance::class, get_class($value));',
                    '$this->assertNotInstanceOf(SomeInstance::class, $value);'
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [MethodCall::class, StaticCall::class];
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames(
            $node,
            ['assertSame', 'assertNotSame', 'assertEquals', 'assertNotEquals']
        )) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        // we need 2 args
        if (! isset($node->args[1])) {
            return null;
        }

        $secondArgument = $node->getArgs()[1];
        $secondArgumentValue = $secondArgument->value;

        if ($secondArgumentValue instanceof FuncCall && $this->isName($secondArgumentValue->name, 'get_class')) {
            $countArg = $secondArgumentValue->getArgs()[0];
            $assertArgs[1] = new Arg($countArg->value);

            $node->args = $assertArgs;
            $this->renameMethod($node);

            return $node;
        }

        return null;
    }

    private function renameMethod(MethodCall|StaticCall $node): void
    {
        if ($this->isNames($node->name, ['assertSame', 'assertEquals'])) {
            $node->name = new Identifier('assertInstanceOf');
        } elseif ($this->isNames($node->name, ['assertNotSame', 'assertNotEquals'])) {
            $node->name = new Identifier('assertNotInstanceOf');
        }
    }
}
