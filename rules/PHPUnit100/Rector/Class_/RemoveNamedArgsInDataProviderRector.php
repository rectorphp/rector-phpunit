<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit100\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\ArrayItem;
use PhpParser\Node\Stmt\Class_;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFinder\DataProviderClassMethodFinder;
use Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\RemoveNamedArgsInDataProviderRector\RemoveNamedArgsInDataProviderRectorTest;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see RemoveNamedArgsInDataProviderRectorTest
 */
final class RemoveNamedArgsInDataProviderRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly DataProviderClassMethodFinder $dataProviderClassMethodFinder,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Remove named arguments in data provider', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield ['namedArg' => 100];
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [100];
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
        return [Class_::class];
    }

    /**
     * @param  Class_  $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $hasChanged = false;

        $dataProviders = $this->dataProviderClassMethodFinder->find($node);
        foreach ($dataProviders as $dataProvider) {
            /** @var Node\Stmt\Expression $stmt */
            foreach ($dataProvider->getStmts() ?? [] as $stmt) {
                $expr = $stmt->expr;
                if ($expr instanceof Node\Expr\Yield_) {
                    $this->handleYieldStmt($expr);
                    $hasChanged = true;
                } elseif ($expr instanceof Node\Expr\Array_) {
                    $this->handleReturnStmt($expr);
                    $hasChanged = true;
                }
            }
        }

        if ($hasChanged) {
            return $node;
        }

        return null;
    }

    private function handleYieldStmt(Node\Expr\Yield_ $expr): void
    {
        /** @var Node\Expr\Array_ $value */
        $value = $expr->value;
        foreach ($value->items as $item) {
            if (! $item instanceof ArrayItem) {
                continue;
            }
            if (! $item->key instanceof Node\Scalar\Int_) {
                $item->key = null;
            }
        }
    }

    private function handleReturnStmt(Node\Expr\Array_ $expr): void
    {
        foreach ($expr->items as $item) {
            if (! $item instanceof ArrayItem) {
                continue;
            }
            if (! $item->key instanceof Node\Scalar\Int_) {
                $item->key = null;
            }
        }
    }
}
