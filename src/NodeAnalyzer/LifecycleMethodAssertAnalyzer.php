<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Comment\Doc;
use PhpParser\Node;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassLike;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Reflection\ClassReflection;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\Enum\ObjectReference;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\Php80\NodeAnalyzer\PhpAttributeAnalyzer;
use Rector\PhpParser\AstResolver;
use Rector\PhpParser\Node\BetterNodeFinder;
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
     * Cheap file pre-check, so ancestor and trait files that cannot declare a hook are not parsed. The analyzed class
     * itself is not pre-checked, as it is passed in. It must never miss a hook, so it matches every spelling of one: the hook method
     * names (in any case, as PHP method names are case-insensitive), the annotations and the attribute class names. An
     * attribute is always written with its class name, whether imported, aliased ("PU\Before") or fully qualified.
     * The attribute names are case-sensitive on purpose, a lowercase "before" is just prose. A false positive only
     * costs a parse.
     */
    private const string HOOK_FILE_PATTERN = '#(?i:\b(?:setUp|tearDown|assertPreConditions|assertPostConditions)\b|@(?:before|after|preCondition|postCondition)\b)|\b(?:Before|After|PreCondition|PostCondition)\b#';

    /**
     * @var array<string, bool>
     */
    private array $assertingByClassAndOverriddenHooks = [];

    public function __construct(
        private readonly ReflectionResolver $reflectionResolver,
        private readonly AstResolver $astResolver,
        private readonly AssertCallAnalyzer $assertCallAnalyzer,
        private readonly PhpAttributeAnalyzer $phpAttributeAnalyzer,
        private readonly PhpDocInfoFactory $phpDocInfoFactory,
        private readonly BetterNodeFinder $betterNodeFinder,
        private readonly NodeNameResolver $nodeNameResolver,
    ) {
    }

    /**
     * The class itself is already parsed by Rector, only its ancestors and traits have to be resolved
     */
    public function hasAssertingLifecycleMethod(Class_ $class): bool
    {
        $classReflection = $this->reflectionResolver->resolveClassReflection($class);
        if (! $classReflection instanceof ClassReflection) {
            return false;
        }

        return $this->resolveHasAssertingLifecycleMethod($classReflection, [], $class);
    }

    /**
     * @param string[] $overriddenHookMethodNames
     */
    private function resolveHasAssertingLifecycleMethod(
        ClassReflection $classReflection,
        array $overriddenHookMethodNames,
        ?Class_ $class = null
    ): bool {
        // do not analyze PHPUnit or Symfony base test cases, their hooks do not assert
        if (in_array($classReflection->getName(), PHPUnitClassName::FRAMEWORK_TEST_CASES, true)) {
            return false;
        }

        // the result of a parent only depends on the hooks overridden below it, so test classes share the parent chain
        sort($overriddenHookMethodNames);
        $cacheKey = $classReflection->getName() . '|' . implode(',', $overriddenHookMethodNames);

        $this->assertingByClassAndOverriddenHooks[$cacheKey] ??= $this->resolveClassTraitsAndParents(
            $classReflection,
            $overriddenHookMethodNames,
            $class
        );

        return $this->assertingByClassAndOverriddenHooks[$cacheKey];
    }

    /**
     * @param string[] $overriddenHookMethodNames
     */
    private function resolveClassTraitsAndParents(
        ClassReflection $classReflection,
        array $overriddenHookMethodNames,
        ?Class_ $class
    ): bool {
        $class ??= $this->resolveClassLike($classReflection);

        $classMethods = $class instanceof ClassLike ? $class->getMethods() : [];
        $newlyOverriddenHookMethodNames = [];

        foreach ($classMethods as $classMethod) {
            $hookMethodName = $this->resolveHookMethodName($classMethod);

            // a hook overridden below hides this one, unless the override calls it through "parent::"
            if ($hookMethodName !== null && ! $this->hasParentCall($classMethod, $hookMethodName)) {
                $newlyOverriddenHookMethodNames[] = $hookMethodName;
            }

            if ($this->isRelevantHook($classMethod, $hookMethodName, $overriddenHookMethodNames)
                && $this->containsAssertCall($classMethod)) {
                return true;
            }
        }

        // hooks from traits are used as if declared in the class, an override of the class itself is ignored to stay safe
        foreach ($classReflection->getTraits(true) as $traitReflection) {
            $trait = $this->resolveClassLike($traitReflection);
            if (! $trait instanceof ClassLike) {
                continue;
            }

            foreach ($trait->getMethods() as $traitMethod) {
                $hookMethodName = $this->resolveHookMethodName($traitMethod);
                if (! $this->isRelevantHook($traitMethod, $hookMethodName, $overriddenHookMethodNames)) {
                    continue;
                }

                if ($this->containsAssertCall($traitMethod)) {
                    return true;
                }
            }
        }

        $parentClassReflection = $classReflection->getParentClass();
        if (! $parentClassReflection instanceof ClassReflection) {
            return false;
        }

        return $this->resolveHasAssertingLifecycleMethod(
            $parentClassReflection,
            array_values(array_unique([...$overriddenHookMethodNames, ...$newlyOverriddenHookMethodNames]))
        );
    }

    private function containsAssertCall(ClassMethod $classMethod): bool
    {
        // every hook gets its own nesting budget, a hook calling "parent::" is evaluated again in the parent itself
        $this->assertCallAnalyzer->resetNesting();

        return $this->assertCallAnalyzer->containsAssertCall($classMethod);
    }

    private function resolveClassLike(ClassReflection $classReflection): ?ClassLike
    {
        if (! $this->mayDeclareHooks($classReflection)) {
            return null;
        }

        return $this->astResolver->resolveClassFromClassReflection($classReflection);
    }

    private function mayDeclareHooks(ClassReflection $classReflection): bool
    {
        $fileName = $classReflection->getFileName();
        if ($fileName === null) {
            return false;
        }

        $fileContents = file_get_contents($fileName);
        if ($fileContents === false) {
            return true;
        }

        return preg_match(self::HOOK_FILE_PATTERN, $fileContents) === 1;
    }

    private function hasParentCall(ClassMethod $classMethod, string $hookMethodName): bool
    {
        return $this->betterNodeFinder->findFirst(
            (array) $classMethod->stmts,
            fn (Node $node): bool => $node instanceof StaticCall
                && $this->nodeNameResolver->isName($node->class, ObjectReference::PARENT)
                && $this->nodeNameResolver->isName($node->name, $hookMethodName)
        ) instanceof StaticCall;
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
     * @param string[] $overriddenHookMethodNames
     */
    private function isRelevantHook(
        ClassMethod $classMethod,
        ?string $hookMethodName,
        array $overriddenHookMethodNames
    ): bool {
        if ($hookMethodName !== null && ! in_array($hookMethodName, $overriddenHookMethodNames, true)) {
            return true;
        }

        // all methods marked as hooks run, also when overridden
        if ($classMethod->attrGroups !== []
            && $this->phpAttributeAnalyzer->hasPhpAttributes($classMethod, self::HOOK_ATTRIBUTES)) {
            return true;
        }

        if (! $classMethod->getDocComment() instanceof Doc) {
            return false;
        }

        return $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod)
            ->hasByNames(self::HOOK_ANNOTATIONS);
    }
}
