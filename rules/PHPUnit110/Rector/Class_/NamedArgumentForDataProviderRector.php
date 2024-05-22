<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit110\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Expr\Yield_;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Return_;
use PHPUnit\Framework\Attributes\DataProvider;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\StaticDataProviderClassMethodRectorTest
 */
final class NamedArgumentForDataProviderRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Change the array-index names to the argument name of the dataProvider',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                    use PHPUnit\Framework\TestCase;

                    final class SomeTest extends TestCase
                    {
                        public static function dataProviderArray(): array
                        {
                            return [
                                [
                                    'keyA' => true,
                                    'keyB' => false,
                                ]
                            ];
                        }

                        #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
                        public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
                        {
                        }
                    }
                    CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                    use PHPUnit\Framework\TestCase;

                    final class SomeTest extends TestCase
                    {
                        public static function dataProviderArray(): array
                        {
                            return [
                                [
                                    'changeToKeyA' => true,
                                    'changeToKeyB' => false,
                                ]
                            ];
                        }

                        #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
                        public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
                        {
                        }
                    }
                    CODE_SAMPLE
                    ,
                ),
            ],
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): Node|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $wasChanged = false;
        foreach ($node->getMethods() as $classMethod) {
            if (! $classMethod->isPublic()) {
                continue;
            }

            if ($classMethod->getParams() === []) {
                continue;
            }

            $dataProviderMethodName = $this->getDataProviderMethodName($classMethod);

            if ($dataProviderMethodName === null) {
                continue;
            }

            $dataProviderMethod = $node->getMethod($dataProviderMethodName);
            if ($dataProviderMethod === null) {
                continue;
            }

            $namedArgumentsFromTestClass = $this->getNamedArguments($classMethod);

            foreach ($this->extractDataProviderArrayItem($dataProviderMethod) as $dataProviderArrayItem) {
                $wasChanged = $this->refactorArrayKey(
                    $dataProviderArrayItem,
                    $namedArgumentsFromTestClass
                ) || $wasChanged;
            }
        }

        return $wasChanged ? $node : null;
    }

    /**
     * @return list<string>
     */
    public function getNamedArguments(ClassMethod $classMethod): array
    {
        $dataProviderNameMapping = [];
        foreach ($classMethod->getParams() as $param) {
            if ($param->var instanceof Variable) {
                $dataProviderNameMapping[] = $this->getName($param->var);
            }
        }

        return array_values(array_filter($dataProviderNameMapping));
    }

    /**
     * @param list<Node\Stmt> $stmts
     * @return array<string, Node\Expr\Array_>
     */
    public function getResolvedVariables(array $stmts): array
    {
        $variables = [];
        foreach ($stmts as $stmt) {
            if (! $stmt instanceof Expression) {
                continue;
            }

            if (! $stmt->expr instanceof Assign) {
                continue;
            }

            if (! $stmt->expr->var instanceof Variable) {
                continue;
            }

            if (! $stmt->expr->expr instanceof Array_) {
                continue;
            }

            $variables[$this->getName($stmt->expr->var)] = $stmt->expr->expr;
        }

        return $variables;
    }

    private function getDataProviderMethodName(ClassMethod $classMethod): string|null
    {
        $attributeClassName = DataProvider::class;
        foreach ($classMethod->attrGroups as $attributeGroup) {
            foreach ($attributeGroup->attrs as $attribute) {
                if (! $this->isName($attribute->name, $attributeClassName)) {
                    continue;
                }

                foreach ($attribute->args as $arg) {
                    if ($arg->value instanceof String_) {
                        return $arg->value->value;
                    }
                }
            }
        }

        return null;
    }

    /**
     * @param list<string> $dataProviderNameMapping
     */
    private function refactorArrayKey(Array_ $array, array $dataProviderNameMapping): bool
    {
        $hasChanged = false;
        $needToSetAllKeyNames = false;

        $allArrayKeyNames = [];

        foreach ($array->items as $arrayItem) {
            if ($arrayItem?->key instanceof String_) {
                $needToSetAllKeyNames = true;
                $allArrayKeyNames[] = $arrayItem->key->value;
            }
        }

        // Skip already modified keys because they could be in a different order
        if (array_intersect($dataProviderNameMapping, $allArrayKeyNames) === $dataProviderNameMapping) {
            return false;
        }

        foreach ($array->items as $arrayIndex => $arrayItem) {
            if ($arrayItem === null) {
                continue;
            }

            if (! isset($dataProviderNameMapping[$arrayIndex])) {
                continue;
            }

            if ($arrayItem->key === null && $needToSetAllKeyNames) {
                $arrayItem->key = String_::fromString($dataProviderNameMapping[$arrayIndex]);
            }

            if ($arrayItem->key instanceof String_ && $arrayItem->key->value !== $dataProviderNameMapping[$arrayIndex]) {
                $arrayItem->key->value = $dataProviderNameMapping[$arrayIndex];
                $hasChanged = true;
            }
        }

        return $hasChanged;
    }

    /**
     * @return iterable<Node\Expr\Array_>
     */
    private function extractDataProviderArrayItem(ClassMethod $classMethod): iterable
    {
        $stmts = $classMethod->getStmts() ?? [];
        $resolvedVariables = $this->getResolvedVariables($stmts);

        foreach ($stmts as $stmt) {
            if ($stmt instanceof Expression && $stmt->expr instanceof Yield_) {
                $arrayItem = $stmt->expr->value;
                if ($arrayItem instanceof Array_) {
                    yield $arrayItem;
                }
            }

            if ($stmt instanceof Return_ && $stmt->expr instanceof Array_) {
                $dataProviderTestCases = $stmt->expr;

                foreach ($dataProviderTestCases->items as $dataProviderTestCase) {
                    $arrayItem = $dataProviderTestCase?->value;

                    if ($arrayItem instanceof Array_) {
                        yield $arrayItem;
                    }

                    $variableName = $arrayItem === null ? null : $this->getName($arrayItem);
                    if (
                        $arrayItem instanceof Variable
                        && $variableName !== null
                        && isset($resolvedVariables[$variableName])
                    ) {
                        $dataProviderList = $resolvedVariables[$variableName];
                        foreach ($dataProviderList->items as $dataProviderItem) {
                            if ($dataProviderItem?->value instanceof Array_) {
                                yield $dataProviderItem->value;
                            }
                        }
                    }
                }
            }
        }
    }
}
