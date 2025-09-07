<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use PhpParser\Node\Scalar;
use PhpParser\Node\Scalar\Float_;
use PhpParser\Node\Scalar\Int_;
use PhpParser\Node\Scalar\String_;
use PHPStan\Reflection\ClassReflection;
use PHPStan\Type\IntegerType;
use PHPStan\Type\StringType;
use PHPStan\Type\Type;
use PHPStan\Type\TypeCombinator;
use Rector\PHPUnit\CodeQuality\Reflection\MethodParametersAndReturnTypesResolver;
use Rector\PHPUnit\Enum\BehatClassName;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Rector\Reflection\ReflectionResolver;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\ScalarArgumentToExpectedParamTypeRectorTest
 */
final class ScalarArgumentToExpectedParamTypeRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly MethodParametersAndReturnTypesResolver $methodParametersAndReturnTypesResolver,
        private readonly ReflectionResolver $reflectionResolver,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Correct expected type in setter of tests, if param type is strictly defined',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeTest extends TestCase
{
    public function test()
    {
        $someClass = new SomeClass();
        $someClass->setPhone(12345);
    }
}

final class SomeClass
{
    public function setPhone(string $phone)
    {
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeTest extends TestCase
{
    public function test()
    {
        $someClass = new SomeClass();
        $someClass->setPhone('12345');
    }
}

final class SomeClass
{
    public function setPhone(string $phone)
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
        return [MethodCall::class, StaticCall::class];
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if ($this->shouldSkipCall($node)) {
            return null;
        }

        $hasChanged = false;
        $callParameterTypes = $this->methodParametersAndReturnTypesResolver->resolveCallParameterTypes($node);
        $callParameterNames = $this->methodParametersAndReturnTypesResolver->resolveCallParameterNames($node);

        foreach ($node->getArgs() as $key => $arg) {
            if (! $arg->value instanceof Scalar) {
                continue;
            }

            $knownParameterType = $callParameterTypes[$key] ?? null;
            if ($arg->name instanceof Identifier) {
                $argName = $arg->name->toString();
                foreach ($callParameterNames as $keyParameterNames => $callParameterName) {
                    if ($argName === $callParameterName) {
                        $knownParameterType = $callParameterTypes[$keyParameterNames] ?? null;
                        break;
                    }
                }
            }

            if (! $knownParameterType instanceof Type) {
                continue;
            }

            // remove null
            $knownParameterType = TypeCombinator::removeNull($knownParameterType);

            if ($knownParameterType instanceof StringType) {
                if ($arg->value instanceof Int_) {
                    $arg->value = new String_((string) $arg->value->value);
                    $hasChanged = true;
                }

                if ($arg->value instanceof Float_) {
                    $arg->value = new String_((string) $arg->value->value);
                    $hasChanged = true;
                }
            }

            if ($knownParameterType instanceof IntegerType && $arg->value instanceof String_) {
                $arg->value = new Int_((int) $arg->value->value);
                $hasChanged = true;
            }
        }

        if (! $hasChanged) {
            return null;
        }

        return $node;
    }

    private function shouldSkipCall(StaticCall|MethodCall $call): bool
    {
        if (! $this->isInTestClass($call)) {
            return true;
        }

        if ($call->isFirstClassCallable()) {
            return true;
        }

        if ($call->getArgs() === []) {
            return true;
        }

        return ! $this->hasStringOrNumberArguments($call);
    }

    private function hasStringOrNumberArguments(StaticCall|MethodCall $call): bool
    {
        foreach ($call->getArgs() as $arg) {
            if ($arg->value instanceof Int_) {
                return true;
            }

            if ($arg->value instanceof String_) {
                return true;
            }

            if ($arg->value instanceof Float_) {
                return true;
            }
        }

        return false;
    }

    private function isInTestClass(StaticCall|MethodCall $call): bool
    {
        $callerClassReflection = $this->reflectionResolver->resolveClassReflection($call);
        if (! $callerClassReflection instanceof ClassReflection) {
            return $this->testsNodeAnalyzer->isInTestClass($call);
        }

        if ($callerClassReflection->is(BehatClassName::CONTEXT)) {
            return true;
        }

        return $this->testsNodeAnalyzer->isInTestClass($call);
    }
}
