<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassMethod;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\PreferTestsWithCamelCaseRector\PreferTestsWithCamelCaseRectorTest
 */
final class PreferTestsWithCamelCaseRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Changes PHPUnit tests methods to camel case', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function test_something()
    {
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function testSomething()
    {
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
        return [ClassMethod::class];
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if (! $this->testsNodeAnalyzer->isTestClassMethod($node)) {
            return null;
        }

        $currentName = $node->name->toString();
        $newName = $this->toCamelCase($currentName);

        if ($currentName === $newName) {
            return null;
        }

        $node->name = new Node\Identifier($newName);

        return $node;
    }

    public function toCamelCase(string $value): string
    {
        $words = explode(' ', str_replace(['-', '_'], ' ', $value));
        $words = array_map(fn (string $word) => ucfirst($word), $words);

        return lcfirst(implode($words));
    }
}
