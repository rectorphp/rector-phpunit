<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\ConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use Rector\PHPUnit\NodeAnalyzer\ArgumentMover;
use Rector\PHPUnit\NodeAnalyzer\IdentifierManipulator;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\ValueObject\ConstantWithAssertMethods;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertSameBoolNullToSpecificMethodRector\AssertSameBoolNullToSpecificMethodRectorTest
 */
final class AssertSameBoolNullToSpecificMethodRector extends AbstractRector
{
    /**
     * @var ConstantWithAssertMethods[]
     */
    private array $constantWithAssertMethods = [];

    public function __construct(
        private readonly IdentifierManipulator $identifierManipulator,
        private readonly ArgumentMover $argumentMover,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
        $this->constantWithAssertMethods = [
            new ConstantWithAssertMethods('null', 'assertNull', 'assertNotNull'),
            new ConstantWithAssertMethods('true', 'assertTrue', 'assertNotTrue'),
            new ConstantWithAssertMethods('false', 'assertFalse', 'assertNotFalse'),
        ];
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns same bool and null comparisons to their method name alternatives in PHPUnit TestCase',
            [
                new CodeSample('$this->assertSame(null, $anything);', '$this->assertNull($anything);'),
                new CodeSample('$this->assertNotSame(false, $anything);', '$this->assertNotFalse($anything);'),
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
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($node, ['assertSame', 'assertNotSame'])) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        $firstArgumentValue = $node->getArgs()[0]
->value;
        if (! $firstArgumentValue instanceof ConstFetch) {
            return null;
        }

        foreach ($this->constantWithAssertMethods as $constantWithAssertMethod) {
            if (! $this->isName($firstArgumentValue, $constantWithAssertMethod->getConstant())) {
                continue;
            }

            $this->renameMethod($node, $constantWithAssertMethod);
            $this->argumentMover->removeFirstArg($node);

            return $node;
        }

        return null;
    }

    private function renameMethod(
        MethodCall|StaticCall $node,
        ConstantWithAssertMethods $constantWithAssertMethods
    ): void {
        $this->identifierManipulator->renameNodeWithMap($node, [
            'assertSame' => $constantWithAssertMethods->getAssetMethodName(),
            'assertNotSame' => $constantWithAssertMethods->getNotAssertMethodName(),
        ]);
    }
}
