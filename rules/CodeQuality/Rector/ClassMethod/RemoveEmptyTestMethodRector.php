<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\NodeTraverser;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveEmptyTestMethodRector\RemoveEmptyTestMethodRectorTest
 */
final class RemoveEmptyTestMethodRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Remove empty test methods', [
            new CodeSample(
                <<<'CODE_SAMPLE'
class SomeTest extends \PHPUnit\Framework\TestCase
{
    /**
     * testGetTranslatedModelField method
     *
     * @return void
     */
    public function testGetTranslatedModelField()
    {
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
class SomeTest extends \PHPUnit\Framework\TestCase
{
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
        return [ClassMethod::class];
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?int
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if (! str_starts_with($node->name->toString(), 'test')) {
            return null;
        }

        if ($node->stmts === null) {
            return null;
        }

        if ($node->stmts !== []) {
            return null;
        }

        return NodeTraverser::REMOVE_NODE;
    }
}
