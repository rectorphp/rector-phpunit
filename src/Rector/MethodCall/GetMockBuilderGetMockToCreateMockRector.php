<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Expression;
use Rector\Core\Rector\AbstractRector;
use Rector\Defluent\NodeAnalyzer\FluentChainMethodCallNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @changelog https://github.com/lmc-eu/steward/pull/187/files#diff-c7e8c65e59b8b4ff8b54325814d4ba55L80
 *
 * @see \Rector\PHPUnit\Tests\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector\GetMockBuilderGetMockToCreateMockRectorTest
 */
final class GetMockBuilderGetMockToCreateMockRector extends AbstractRector
{
    /**
     * @var string[]
     */
    private const USELESS_METHOD_NAMES = [
        'disableOriginalConstructor',
        'onlyMethods',
        'setMethods',
        'setMethodsExcept',
    ];

    public function __construct(private readonly FluentChainMethodCallNodeAnalyzer $fluentChainMethodCallNodeAnalyzer)
    {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Remove getMockBuilder() to createMock()', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $applicationMock = $this->getMockBuilder('SomeClass')
           ->disableOriginalConstructor()
           ->getMock();
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
        $applicationMock = $this->createMock('SomeClass');
    }
}
CODE_SAMPLE
            ),
        ]);
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [MethodCall::class];
    }

    /**
     * @param MethodCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->isName($node->name, 'getMock')) {
            return null;
        }

        if (! $node->var instanceof MethodCall) {
            return null;
        }

        // traverse up over useless methods until we reach the top one
        $currentMethodCall = $node->var;
        $currentStatement = $this->betterNodeFinder->resolveCurrentStatement($node);

        while ($currentMethodCall instanceof MethodCall && $this->isNames(
            $currentMethodCall->name,
            self::USELESS_METHOD_NAMES
        )) {
            if ($this->shouldSkip($node, $currentMethodCall, $currentStatement)) {
                return null;
            }

            $currentMethodCall = $currentMethodCall->var;
        }

        if (! $currentMethodCall instanceof MethodCall) {
            return null;
        }

        if (! $this->isName($currentMethodCall->name, 'getMockBuilder')) {
            return null;
        }

        $args = $currentMethodCall->args;
        $thisVariable = $currentMethodCall->var;

        return new MethodCall($thisVariable, 'createMock', $args);
    }

    private function shouldSkip(MethodCall $originalMethodCall, MethodCall $partMethodCall, ?Stmt $stmt): bool
    {
        if (! $stmt instanceof Expression) {
            return false;
        }

        if (! $stmt->expr instanceof Assign) {
            return false;
        }

        if ($stmt->expr->expr !== $originalMethodCall) {
            return false;
        }

        if (! $this->isName($partMethodCall->name, 'onlyMethods')) {
            return false;
        }

        $assignVariable = $stmt->expr->var;
        return (bool) $this->betterNodeFinder->findFirstNext($stmt, function (Node $subNode) use (
            $assignVariable
        ): bool {
            if (! $subNode instanceof MethodCall) {
                return false;
            }

            $root = $this->fluentChainMethodCallNodeAnalyzer->resolveRootExpr($subNode);
            if (! $this->nodeComparator->areNodesEqual($root, $assignVariable)) {
                return false;
            }

            return $this->isName($subNode->name, 'method');
        });
    }
}
