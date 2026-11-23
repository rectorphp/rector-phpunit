<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit120\Rector\CallLike;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\ArrayItem;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\New_;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use PhpParser\NodeVisitor;
use PHPStan\Reflection\FunctionReflection;
use PHPStan\Reflection\MethodReflection;
use PHPStan\Reflection\ParameterReflection;
use PHPStan\Reflection\ParametersAcceptor;
use PHPStan\Type\MixedType;
use PHPStan\Type\ObjectType;
use Rector\NodeTypeResolver\PHPStan\ParametersAcceptorSelectorVariantsWrapper;
use Rector\PhpParser\AstResolver;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\PHPStan\ScopeFetcher;
use Rector\PHPUnit\CodeQuality\NodeAnalyser\MockObjectExprDetector;
use Rector\PHPUnit\Enum\PHPUnitClassName;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Rector\Reflection\ReflectionResolver;
use Rector\RuleDoc\CodeSample\CodeSample;
use Rector\RuleDoc\RuleDefinition;
use Rector\VersionBonding\Contract\ComposerPackageConstraintInterface;
use Rector\VersionBonding\ValueObject\ComposerPackageConstraint;

/**
 * Related change in PHPUnit 12 https://phpunit.expert/articles/testing-with-and-without-dependencies.html
 *
 * @see \Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\CreateStubOverCreateMockArgRectorTest
 */
final class CreateStubOverCreateMockArgRector extends AbstractRector implements ComposerPackageConstraintInterface
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly MockObjectExprDetector $mockObjectExprDetector,
        private readonly ReflectionResolver $reflectionResolver,
        private readonly AstResolver $astResolver,
        private readonly BetterNodeFinder $betterNodeFinder
    ) {
    }

    public function provideComposerPackageConstraint(): ComposerPackageConstraint
    {
        return new ComposerPackageConstraint('phpunit/phpunit', '>=11.0');
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Use createStub() over createMock() when used as argument or array value and does not add any mock requirements',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;
final class SomeTest extends TestCase
{
    public function test()
    {
        $this->someMethod($this->createMock(SomeClass::class));
    }

    private function someMethod($someClass)
    {
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
        $this->someMethod($this->createStub(SomeClass::class));
    }

    private function someMethod($someClass)
    {
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
        return [StaticCall::class, MethodCall::class, New_::class, ClassMethod::class];
    }

    /**
     * @param MethodCall|StaticCall|New_|ClassMethod $node
     */
    public function refactor(Node $node): MethodCall|StaticCall|New_|ClassMethod|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if ($node instanceof ClassMethod) {
            $refactoredClassMethod = $this->refactorArrayItems($node);
            return $this->refactorClassMethod($node) ?? $refactoredClassMethod;
        }

        $hasChanges = false;

        if ($node->isFirstClassCallable()) {
            return null;
        }

        $scope = ScopeFetcher::fetch($node);
        $reflection = $this->reflectionResolver->resolveFunctionLikeReflectionFromCall($node);

        if (! $reflection instanceof FunctionReflection && ! $reflection instanceof MethodReflection) {
            return null;
        }

        $parametersAcceptor = ParametersAcceptorSelectorVariantsWrapper::select($reflection, $node, $scope);

        foreach ($node->getArgs() as $key => $arg) {
            if (! $arg->value instanceof MethodCall) {
                continue;
            }

            $parameter = $this->matchParameter($parametersAcceptor, $arg, $key);
            $type = $parameter?->getType() ?? new MixedType();
            $superType = new ObjectType(PHPUnitClassName::MOCK_OBJECT);

            if ($superType->isSuperTypeOf($type)->yes()) {
                continue;
            }

            $methodCall = $arg->value;
            if (! $this->isName($methodCall->name, 'createMock')) {
                continue;
            }

            // the mock can be configured later through the property
            if ($parameter instanceof ParameterReflection && $this->isStoredInProperty(
                $node,
                $reflection,
                $parameter->getName()
            )) {
                continue;
            }

            $methodCall->name = new Identifier('createStub');
            $hasChanges = true;
        }

        if ($hasChanges) {
            return $node;
        }

        return null;
    }

    private function matchParameter(ParametersAcceptor $parametersAcceptor, Arg $arg, int $key): ?ParameterReflection
    {
        $parameters = $parametersAcceptor->getParameters();
        if (! $arg->name instanceof Identifier) {
            $lastParameter = $parameters[count($parameters) - 1] ?? null;

            return $parameters[$key] ?? ($lastParameter?->isVariadic() ? $lastParameter : null);
        }

        foreach ($parameters as $parameter) {
            if ($parameter->getName() === $arg->name->toString()) {
                return $parameter;
            }
        }

        return null;
    }

    private function matchCreateMockMethodCall(Expr $expr): null|MethodCall
    {
        if (! $expr instanceof MethodCall) {
            return null;
        }

        if (! $this->isName($expr->name, 'createMock')) {
            return null;
        }

        return $expr;
    }

    private function refactorClassMethod(ClassMethod $classMethod): ?ClassMethod
    {
        if (! $this->testsNodeAnalyzer->isTestClassMethod($classMethod)) {
            return null;
        }

        $hasChanged = false;
        foreach ((array) $classMethod->stmts as $stmt) {
            if (! $stmt instanceof Expression) {
                continue;
            }

            if (! $stmt->expr instanceof Assign) {
                continue;
            }

            $assign = $stmt->expr;

            // handled in another rule
            if ($assign->var instanceof PropertyFetch) {
                continue;
            }

            $createMockMethodCall = $this->matchCreateMockMethodCall($assign->expr);

            if (! $createMockMethodCall instanceof MethodCall) {
                continue;
            }

            // no change, as we use the variable for mocking later
            if ($this->mockObjectExprDetector->isUsedForMocking($assign->var, $classMethod)) {
                continue;
            }

            $createMockMethodCall->name = new Identifier('createStub');
            $hasChanged = true;
        }

        if ($hasChanged) {
            return $classMethod;
        }

        return null;
    }

    private function refactorArrayItems(ClassMethod $classMethod): ?ClassMethod
    {
        $hasChanged = false;

        $this->traverseNodesWithCallable((array) $classMethod->stmts, function (Node $node) use (&$hasChanged): ?int {
            // the mock can be configured later through the property
            if ($node instanceof Assign && $node->expr instanceof Array_ && $this->isPropertyAssignVar($node->var)) {
                return NodeVisitor::DONT_TRAVERSE_CHILDREN;
            }

            if (! $node instanceof ArrayItem) {
                return null;
            }

            $createMockMethodCall = $this->matchCreateMockMethodCall($node->value);
            if (! $createMockMethodCall instanceof MethodCall) {
                return null;
            }

            // e.g. nested anonymous class
            if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
                return null;
            }

            $createMockMethodCall->name = new Identifier('createStub');
            $hasChanged = true;

            return null;
        });

        return $hasChanged ? $classMethod : null;
    }

    private function isStoredInProperty(
        MethodCall|StaticCall|New_ $callLike,
        MethodReflection|FunctionReflection $reflection,
        string $parameterName
    ): bool {
        if (! $reflection instanceof MethodReflection) {
            return false;
        }

        $isSelfCall = ($callLike instanceof MethodCall && $this->isName($callLike->var, 'this'))
            || ($callLike instanceof StaticCall && $this->isName($callLike->class, 'parent'));
        if (! $isSelfCall) {
            return false;
        }

        $classMethod = $this->astResolver->resolveClassMethod(
            $reflection->getDeclaringClass()
                ->getName(),
            $reflection->getName()
        );
        if (! $classMethod instanceof ClassMethod) {
            return false;
        }

        $assigns = $this->betterNodeFinder->findInstanceOf((array) $classMethod->stmts, Assign::class);

        return array_any(
            $assigns,
            fn (Assign $assign): bool => $this->isPropertyAssignVar($assign->var)
                && $this->betterNodeFinder->findFirst(
                    $assign->expr,
                    fn (Node $node): bool => $node instanceof Variable && $this->isName($node, $parameterName)
                ) instanceof Node
        );
    }

    private function isPropertyAssignVar(Expr $expr): bool
    {
        while ($expr instanceof ArrayDimFetch) {
            $expr = $expr->var;
        }

        return $expr instanceof PropertyFetch;
    }
}
