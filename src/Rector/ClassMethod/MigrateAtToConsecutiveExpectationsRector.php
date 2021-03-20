<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\ExpectationAnalyzer;
use Rector\PHPUnit\NodeFactory\ConsecutiveAssertionFactory;
use Rector\PHPUnit\ValueObject\ExpectationMock;
use Rector\PHPUnit\ValueObject\ExpectationMockCollection;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\MigrateAtToConsecutiveExpectationsRectorTest
 */
final class MigrateAtToConsecutiveExpectationsRector extends AbstractRector
{
    /**
     * @var ConsecutiveAssertionFactory
     */
    private $consecutiveAssertionFactory;

    /**
     * @var ExpectationAnalyzer
     */
    private $expectationAnalyzer;

    public function __construct(
        ConsecutiveAssertionFactory $consecutiveAssertionFactory,
        ExpectationAnalyzer $expectationAnalyzer
    ) {
        $this->consecutiveAssertionFactory = $consecutiveAssertionFactory;
        $this->expectationAnalyzer = $expectationAnalyzer;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Migrates deprecated $this->at to $this->withConsecutive and $this->willReturnOnConsecutiveCalls',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
$mock = $this->createMock(Foo::class);
$mock->expects($this->at(0))->with('0')->method('someMethod')->willReturn('1');
$mock->expects($this->at(1))->with('1')->method('someMethod')->willReturn('2');
CODE_SAMPLE
,
                    <<<'CODE_SAMPLE'
$mock = $this->createMock(Foo::class);
$mock->method('someMethod')->withConsecutive(['0'], ['1'])->willReturnOnConsecutiveCalls('1', '2');
CODE_SAMPLE

                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [ClassMethod::class];
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        $stmts = $node->stmts;
        if ($stmts === null) {
            return null;
        }

        $expressions = array_filter($stmts, function (Stmt $expr): bool {
            return $expr instanceof Expression && $expr->expr instanceof MethodCall;
        });

        $expectationMockCollection = $this->expectationAnalyzer->getExpectationsFromExpressions($expressions);

        if (! $expectationMockCollection->hasExpectationMocks()) {
            return null;
        }

        $expectationCollections = $this->groupExpectationCollectionsByVariableName($expectationMockCollection);
        foreach ($expectationCollections as $expectationCollection) {
            $this->replaceExpectationNodes($expectationCollection);
        }

        return $node;
    }

    private function buildNewExpectation(ExpectationMockCollection $expectationMockCollection): MethodCall
    {
        $this->fillMissingAtIndexes($expectationMockCollection);

        return $this->consecutiveAssertionFactory->createAssertionFromExpectationMockCollection(
            $expectationMockCollection
        );
    }

    private function fillMissingAtIndexes(ExpectationMockCollection $expectationMockCollection): void
    {
        $variable = $expectationMockCollection->getExpectationMocks()[0]
            ->getExpectationVariable();

        // OR
        if ($expectationMockCollection->getLowestAtIndex() !== 0) {
            for ($i = 0; $i < $expectationMockCollection->getLowestAtIndex(); ++$i) {
                $expectationMockCollection->add(new ExpectationMock($variable, [], $i, null, [], null));
            }
        }

        if ($expectationMockCollection->isMissingAtIndexBetweenHighestAndLowest()) {
            $existingIndexes = array_column($expectationMockCollection->getExpectationMocks(), 'index');
            for ($i = 1; $i < $expectationMockCollection->getHighestAtIndex(); ++$i) {
                if (! in_array($i, $existingIndexes, true)) {
                    $expectationMockCollection->add(new ExpectationMock($variable, [], $i, null, [], null));
                }
            }
        }
    }

    private function replaceExpectationNodes(ExpectationMockCollection $expectationMockCollection): void
    {
        if ($this->shouldSkipReplacement($expectationMockCollection)) {
            return;
        }

        $endLines = array_map(static function (ExpectationMock $expectationMock): int {
            $originalExpression = $expectationMock->getOriginalExpression();
            return $originalExpression instanceof Expression ? $originalExpression->getEndLine() : 0;
        }, $expectationMockCollection->getExpectationMocks());
        $max = max($endLines);

        foreach ($expectationMockCollection->getExpectationMocks() as $expectationMock) {
            $originalExpression = $expectationMock->getOriginalExpression();
            if (! $originalExpression instanceof Expression) {
                continue;
            }
            if ($max > $originalExpression->getEndLine()) {
                $this->removeNode($originalExpression);
            } else {
                $originalExpression->expr = $this->buildNewExpectation($expectationMockCollection);
            }
        }
    }

    private function shouldSkipReplacement(ExpectationMockCollection $expectationMockCollection): bool
    {
        if (! $expectationMockCollection->hasReturnValues()) {
            return false;
        }

        if (! $expectationMockCollection->isExpectedMethodAlwaysTheSame()) {
            return true;
        }

        if ($expectationMockCollection->hasMissingAtIndexes()) {
            return true;
        }
        return $expectationMockCollection->hasMissingReturnValues();
    }

    /**
     * @return ExpectationMockCollection[]
     */
    private function groupExpectationCollectionsByVariableName(
        ExpectationMockCollection $expectationMockCollection
    ): array {
        $groupedByVariable = [];
        foreach ($expectationMockCollection->getExpectationMocks() as $expectationMock) {
            $variable = $expectationMock->getExpectationVariable();
            if (! is_string($variable->name)) {
                continue;
            }
            if (! isset($groupedByVariable[$variable->name])) {
                $groupedByVariable[$variable->name] = new ExpectationMockCollection();
            }
            $groupedByVariable[$variable->name]->add($expectationMock);
        }

        return array_values($groupedByVariable);
    }
}
