<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use PhpParser\PrettyPrinter\Standard;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

final class NarrowIdenticalWithConsecutiveRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Narrow identical withConsecutive() to single call',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $this->personServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->withConsecutive(
                [1],
                [1],
                [1],
            );
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $this->personServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->with([1]);
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<MethodCall|StaticCall>>
     */
    public function getNodeTypes(): array
    {
        return [MethodCall::class];
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    public function refactor(Node $node): MethodCall|StaticCall|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if (! $this->isName($node->name, 'withConsecutive')) {
            return null;
        }

        $printerStandard = new Standard();

        $cachedValues = [];
        foreach ($node->getArgs() as $arg) {
            $cachedValues[] = $printerStandard->prettyPrintExpr($arg->value);
        }

        $uniqueArgValues = array_unique($cachedValues);

        // multiple unique values
        if (count($uniqueArgValues) !== 1) {
            return null;
        }

        $firstArg = $node->getArgs()[0];

        // use simpler with() instead
        $node->name = new Identifier('with');
        $node->args = [new Arg($firstArg->value)];

        return $node;
    }
}
