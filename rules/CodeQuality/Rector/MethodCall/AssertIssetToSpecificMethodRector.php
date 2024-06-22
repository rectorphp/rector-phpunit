<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\Isset_;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use Rector\PHPUnit\Enum\AssertMethod;
use Rector\PHPUnit\NodeAnalyzer\IdentifierManipulator;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\AssertIssetToSpecificMethodRectorTest
 */
final class AssertIssetToSpecificMethodRector extends AbstractRector
{
    public function __construct(
        private readonly IdentifierManipulator $identifierManipulator,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns assertTrue() + isset() comparisons to more precise assertArrayHasKey() method',
            [
                new CodeSample(
                    '$this->assertTrue(isset($anything["foo"]), "message");',
                    '$this->assertArrayHasKey("foo", $anything, "message");'
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
            [AssertMethod::ASSERT_TRUE, AssertMethod::ASSERT_FALSE]
        )) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        $firstArg = $node->getArgs()[0];
        $firstArgumentValue = $firstArg->value;

        // is property access
        if (! $firstArgumentValue instanceof Isset_) {
            return null;
        }

        $issetVariable = $firstArgumentValue->vars[0];
        if (! $issetVariable instanceof ArrayDimFetch) {
            return null;
        }

        return $this->refactorArrayDimFetchNode($node, $issetVariable);
    }

    private function refactorArrayDimFetchNode(MethodCall|StaticCall $node, ArrayDimFetch $arrayDimFetch): Node
    {
        $this->identifierManipulator->renameNodeWithMap($node, [
            AssertMethod::ASSERT_TRUE => 'assertArrayHasKey',
            AssertMethod::ASSERT_FALSE => 'assertArrayNotHasKey',
        ]);

        $oldArgs = $node->getArgs();
        unset($oldArgs[0]);

        $node->args = [...$this->nodeFactory->createArgs([$arrayDimFetch->dim, $arrayDimFetch->var]), ...$oldArgs];
        return $node;
    }
}
