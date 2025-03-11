<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Name\FullyQualified;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Foreach_;
use PHPStan\Type\Type;
use PHPStan\Type\TypeCombinator;
use PHPStan\Type\UnionType;
use Rector\PHPUnit\CodeQuality\NodeAnalyser\NullableObjectAssignCollector;
use Rector\PHPUnit\CodeQuality\ValueObject\VariableNameToType;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\AddInstanceofAssertForNullableInstanceRectorTest
 */
final class AddInstanceofAssertForNullableInstanceRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly NullableObjectAssignCollector $nullableObjectAssignCollector,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add explicit instance assert between nullable object assign and method call on nullable object (spotted by PHPStan)',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someObject = $this->getSomeObject();

        $value = $someObject->getSomeMethod();
    }

    private function getSomeObject(): ?SomeClass
    {
        if (mt_rand(0, 1)) {
            return new SomeClass();
        }

        return null;
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
        $someObject = $this->getSomeObject();
        $this->assertInstanceof(SomeClass::class, $someObject);

        $value = $someObject->getSomeMethod();
    }

    private function getSomeObject(): ?SomeClass
    {
        if (mt_rand(0, 1)) {
            return new SomeClass();
        }

        return null;
    }
}
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
        return [ClassMethod::class, Foreach_::class];
    }

    /**
     * @param ClassMethod|Foreach_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if ($node->stmts === [] || $node->stmts === null) {
            return null;
        }

        $hasChanged = false;

        /** @var VariableNameToType[] $nullableVariableNamesToTypes */
        $nullableVariableNamesToTypes = [];

        foreach ($node->stmts as $key => $stmt) {
            if ($stmt instanceof Expression && $stmt->expr instanceof Assign) {
                $variableNameToType = $this->nullableObjectAssignCollector->collect($stmt->expr);
                if ($variableNameToType instanceof VariableNameToType) {
                    $nullableVariableNamesToTypes[] = $variableNameToType;
                    continue;
                }
            }

            // has callable on nullable variable of already collected name?
            $matchedNullableVariableNameToType = $this->matchedNullableVariableNameToType(
                $stmt,
                $nullableVariableNamesToTypes
            );
            if (! $matchedNullableVariableNameToType instanceof VariableNameToType) {
                continue;
            }

            // adding type here + popping the variable name out
            $assertInstanceofExpression = $this->createAssertInstanceof($matchedNullableVariableNameToType);
            array_splice($node->stmts, $key, 0, [$assertInstanceofExpression]);

            // remove variable name from nullable ones
            $hasChanged = true;

            // from now on, the variable is not nullable, remove to avoid double asserts
            foreach ($nullableVariableNamesToTypes as $key => $nullableVariableNamesToType) {
                if ($matchedNullableVariableNameToType === $nullableVariableNamesToType) {
                    unset($nullableVariableNamesToTypes[$key]);
                }
            }
        }

        if (! $hasChanged) {
            return null;
        }

        return $node;
    }

    private function isNullableType(Type $type): bool
    {
        if (! $type instanceof UnionType) {
            return false;
        }

        if (! TypeCombinator::containsNull($type)) {
            return false;
        }

        return count($type->getTypes()) === 2;
    }

    private function createAssertInstanceof(VariableNameToType $variableNameToType): Expression
    {
        $args = [
            new Arg(new ClassConstFetch(new FullyQualified($variableNameToType->getObjectType()), 'class')),
            new Arg(new Variable($variableNameToType->getVariableName())),
        ];

        $methodCall = new MethodCall(new Variable('this'), 'assertInstanceof', $args);

        return new Expression($methodCall);
    }

    /**
     * @param VariableNameToType[] $nullableVariableNamesToTypes
     */
    private function matchNullableVariableNameToType(
        array $nullableVariableNamesToTypes,
        Variable $variable
    ): ?VariableNameToType {
        $variableName = $this->getName($variable);

        foreach ($nullableVariableNamesToTypes as $nullableVariableNameToType) {
            if ($nullableVariableNameToType->getVariableName() !== $variableName) {
                continue;
            }

            return $nullableVariableNameToType;
        }

        return null;
    }

    /**
     * @param VariableNameToType[] $variableNamesToTypes
     */
    private function matchedNullableVariableNameToType(
        Stmt $stmt,
        array $variableNamesToTypes
    ): ?VariableNameToType {
        $matchedNullableVariableNameToType = null;

        $this->traverseNodesWithCallable($stmt, function (Node $node) use (
            $variableNamesToTypes,
            &$matchedNullableVariableNameToType
        ): null {
            if (! $node instanceof MethodCall) {
                return null;
            }

            if (! $node->var instanceof Variable) {
                return null;
            }

            $variableType = $this->getType($node->var);
            if (! $this->isNullableType($variableType)) {
                return null;
            }

            // is the variable we're interested in?
            $matchedNullableVariableNameToType = $this->matchNullableVariableNameToType(
                $variableNamesToTypes,
                $node->var
            );

            return null;
        });

        return $matchedNullableVariableNameToType;
    }
}
