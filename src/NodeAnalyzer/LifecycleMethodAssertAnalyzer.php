<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Reflection\ClassReflection;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\Php80\NodeAnalyzer\PhpAttributeAnalyzer;
use Rector\PhpParser\AstResolver;
use Rector\PHPUnit\Enum\PHPUnitAttribute;
use Rector\PHPUnit\Enum\PHPUnitClassName;
use Rector\Reflection\ReflectionResolver;

/**
 * PHPUnit counts assertions made in lifecycle methods toward every test of the class,
 * so no test in such a class can be a test without assertions.
 */
final class LifecycleMethodAssertAnalyzer
{
    /**
     * @var string[]
     */
    private const array HOOK_METHOD_NAMES = ['setUp', 'tearDown', 'assertPreConditions', 'assertPostConditions'];

    /**
     * @var string[]
     */
    private const array HOOK_ATTRIBUTES = [
        PHPUnitAttribute::BEFORE,
        PHPUnitAttribute::AFTER,
        PHPUnitAttribute::PRE_CONDITION,
        PHPUnitAttribute::POST_CONDITION,
    ];

    /**
     * @var string[]
     */
    private const array HOOK_ANNOTATIONS = ['before', 'after', 'preCondition', 'postCondition'];

    /**
     * @var array<string, bool>
     */
    private array $assertingByClassName = [];

    public function __construct(
        private readonly ReflectionResolver $reflectionResolver,
        private readonly AstResolver $astResolver,
        private readonly AssertCallAnalyzer $assertCallAnalyzer,
        private readonly PhpAttributeAnalyzer $phpAttributeAnalyzer,
        private readonly PhpDocInfoFactory $phpDocInfoFactory,
    ) {
    }

    public function hasAssertingLifecycleMethod(ClassMethod $classMethod): bool
    {
        $classReflection = $this->reflectionResolver->resolveClassReflection($classMethod);
        if (! $classReflection instanceof ClassReflection) {
            return false;
        }

        $className = $classReflection->getName();
        $this->assertingByClassName[$className] ??= $this->resolveHasAssertingLifecycleMethod($classReflection);

        return $this->assertingByClassName[$className];
    }

    private function resolveHasAssertingLifecycleMethod(ClassReflection $classReflection): bool
    {
        // only the most derived override of a hook is called by PHPUnit, parents are reached via "parent::" calls
        $seenHookMethodNames = [];

        for (
            $currentClassReflection = $classReflection;
            $currentClassReflection instanceof ClassReflection;
            $currentClassReflection = $currentClassReflection->getParentClass()
        ) {
            // do not analyze PHPUnit itself
            if ($currentClassReflection->getName() === PHPUnitClassName::TEST_CASE) {
                return false;
            }

            $class = $this->astResolver->resolveClassFromClassReflection($currentClassReflection);
            if (! $class instanceof Class_) {
                continue;
            }

            $hookMethodNamesOfClass = [];

            foreach ($class->getMethods() as $hookCandidate) {
                $hookMethodName = $this->resolveHookMethodName($hookCandidate);
                if ($hookMethodName !== null) {
                    $hookMethodNamesOfClass[] = $hookMethodName;
                }

                if (! $this->isRelevantHook($hookCandidate, $hookMethodName, $seenHookMethodNames)) {
                    continue;
                }

                $this->assertCallAnalyzer->resetNesting();
                if ($this->assertCallAnalyzer->containsAssertCall($hookCandidate)) {
                    return true;
                }
            }

            $seenHookMethodNames = array_merge($seenHookMethodNames, $hookMethodNamesOfClass);
        }

        return false;
    }

    private function resolveHookMethodName(ClassMethod $classMethod): ?string
    {
        $methodName = $classMethod->name->toString();

        foreach (self::HOOK_METHOD_NAMES as $hookMethodName) {
            if (strcasecmp($hookMethodName, $methodName) === 0) {
                return $hookMethodName;
            }
        }

        return null;
    }

    /**
     * @param string[] $seenHookMethodNames
     */
    private function isRelevantHook(ClassMethod $classMethod, ?string $hookMethodName, array $seenHookMethodNames): bool
    {
        if ($hookMethodName !== null && ! in_array($hookMethodName, $seenHookMethodNames, true)) {
            return true;
        }

        // all methods marked as hooks run, also when overridden
        if ($this->phpAttributeAnalyzer->hasPhpAttributes($classMethod, self::HOOK_ATTRIBUTES)) {
            return true;
        }

        return $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod)
            ->hasByNames(self::HOOK_ANNOTATIONS);
    }
}
