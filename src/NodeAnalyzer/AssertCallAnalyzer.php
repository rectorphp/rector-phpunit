<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\PrettyPrinter\Standard;
use PHPStan\Type\TypeWithClassName;
use Rector\Core\PhpParser\AstResolver;
use Rector\Core\PhpParser\Node\BetterNodeFinder;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\NodeTypeResolver\NodeTypeResolver;
use Rector\StaticTypeMapper\ValueObject\Type\FullyQualifiedObjectType;

final class AssertCallAnalyzer
{
    /**
     * @var int
     */
    private const MAX_NESTED_METHOD_CALL_LEVEL = 3;

    /**
     * @var array<string, bool>
     */
    private array $containsAssertCallByClassMethod = [];

    /**
     * This should prevent segfaults while going too deep into to parsed code. Without it, it might end-up with segfault
     */
    private int $classMethodNestingLevel = 0;

    public function __construct(
        private readonly AstResolver $astResolver,
        private readonly Standard $printerStandard,
        private readonly BetterNodeFinder $betterNodeFinder,
        private readonly NodeNameResolver $nodeNameResolver,
        private readonly NodeTypeResolver $nodeTypeResolver,
    ) {
    }

    public function resetNesting(): void
    {
        $this->classMethodNestingLevel = 0;
    }

    public function containsAssertCall(ClassMethod $classMethod): bool
    {
        ++$this->classMethodNestingLevel;

        // probably no assert method in the end
        if ($this->classMethodNestingLevel > self::MAX_NESTED_METHOD_CALL_LEVEL) {
            return false;
        }

        $cacheHash = md5($this->printerStandard->prettyPrint([$classMethod]));

        if (isset($this->containsAssertCallByClassMethod[$cacheHash])) {
            return $this->containsAssertCallByClassMethod[$cacheHash];
        }

        // A. try "->assert" shallow search first for performance
        $hasDirectAssertCall = $this->hasDirectAssertCall($classMethod);
        if ($hasDirectAssertCall) {
            $this->containsAssertCallByClassMethod[$cacheHash] = $hasDirectAssertCall;
            return true;
        }

        // B. look for nested calls
        $hasNestedAssertCall = $this->hasNestedAssertCall($classMethod);
        $this->containsAssertCallByClassMethod[$cacheHash] = $hasNestedAssertCall;

        return $hasNestedAssertCall;
    }

    private function hasDirectAssertCall(ClassMethod $classMethod): bool
    {
        return (bool) $this->betterNodeFinder->findFirst((array) $classMethod->stmts, function (Node $node): bool {
            if ($node instanceof MethodCall) {
                $type = $this->nodeTypeResolver->getType($node->var);

                if ($type instanceof FullyQualifiedObjectType && in_array(
                    $type->getClassName(),
                    ['PHPUnit\Framework\MockObject\MockBuilder', 'Prophecy\Prophet'],
                    true
                )) {
                    return true;
                }

                return $this->isAssertMethodName($node);
            }

            if ($node instanceof StaticCall) {
                return $this->isAssertMethodName($node);
            }

            return false;
        });
    }

    private function hasNestedAssertCall(ClassMethod $classMethod): bool
    {
        $currentClassMethod = $classMethod;

        // over and over the same method :/
        return (bool) $this->betterNodeFinder->findFirst((array) $classMethod->stmts, function (Node $node) use (
            $currentClassMethod
        ): bool {
            if (! $node instanceof MethodCall && ! $node instanceof StaticCall) {
                return false;
            }

            $classMethod = $this->resolveClassMethodFromCall($node);

            // skip circular self calls
            if ($currentClassMethod === $classMethod) {
                return false;
            }

            if ($classMethod !== null) {
                return $this->containsAssertCall($classMethod);
            }

            return false;
        });
    }

    private function resolveClassMethodFromCall(StaticCall | MethodCall $call): ?ClassMethod
    {
        if ($call instanceof MethodCall) {
            $objectType = $this->nodeTypeResolver->getType($call->var);
        } else {
            // StaticCall
            $objectType = $this->nodeTypeResolver->getType($call->class);
        }

        if (! $objectType instanceof TypeWithClassName) {
            return null;
        }

        $methodName = $this->nodeNameResolver->getName($call->name);
        if ($methodName === null) {
            return null;
        }

        return $this->astResolver->resolveClassMethod($objectType->getClassName(), $methodName);
    }

    private function isAssertMethodName(MethodCall|StaticCall $call): bool
    {
        return $this->nodeNameResolver->isNames($call->name, [
            // phpunit
            '*assert',
            'assert*',
            'expectException*',
            'setExpectedException*',
        ]);
    }
}
