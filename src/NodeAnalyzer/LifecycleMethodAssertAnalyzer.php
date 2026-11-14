<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Comment\Doc;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\Php80\NodeAnalyzer\PhpAttributeAnalyzer;
use Rector\PHPUnit\Enum\PHPUnitAttribute;
use WeakMap;

/**
 * PHPUnit counts assertions made in lifecycle methods toward every test of the class
 */
final readonly class LifecycleMethodAssertAnalyzer
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
     * @var WeakMap<Class_, bool>
     */
    private WeakMap $assertingByClass;

    public function __construct(
        private AssertCallAnalyzer $assertCallAnalyzer,
        private PhpAttributeAnalyzer $phpAttributeAnalyzer,
        private PhpDocInfoFactory $phpDocInfoFactory,
        private NodeNameResolver $nodeNameResolver,
    ) {
        $this->assertingByClass = new WeakMap();
    }

    public function hasAssertingLifecycleMethod(Class_ $class): bool
    {
        // every test method of the class shares the result
        return $this->assertingByClass[$class] ??= $this->resolveHasAssertingLifecycleMethod($class);
    }

    private function resolveHasAssertingLifecycleMethod(Class_ $class): bool
    {
        foreach ($class->getMethods() as $classMethod) {
            if (! $this->isLifecycleMethod($classMethod)) {
                continue;
            }

            $this->assertCallAnalyzer->resetNesting();
            if ($this->assertCallAnalyzer->containsAssertCall($classMethod)) {
                return true;
            }
        }

        return false;
    }

    private function isLifecycleMethod(ClassMethod $classMethod): bool
    {
        if ($this->nodeNameResolver->isNames($classMethod->name, self::HOOK_METHOD_NAMES)) {
            return true;
        }

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
