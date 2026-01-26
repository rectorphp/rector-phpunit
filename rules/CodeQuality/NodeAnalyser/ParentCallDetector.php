<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use Rector\NodeNameResolver\NodeNameResolver;

final readonly class ParentCallDetector
{
    public function __construct(
        private NodeNameResolver $nodeNameResolver
    ) {
    }

    public function hasParentCall(ClassMethod $classMethod): bool
    {
        $methodName = $classMethod->name->toString();

        foreach ((array) $classMethod->stmts as $stmt) {
            if (! $stmt instanceof Expression) {
                continue;
            }

            if (! $stmt->expr instanceof StaticCall) {
                continue;
            }

            $staticCall = $stmt->expr;
            if (! $this->nodeNameResolver->isName($staticCall->class, 'parent')) {
                continue;
            }

            if (! $this->nodeNameResolver->isName($staticCall->name, $methodName)) {
                continue;
            }

            return true;
        }

        return false;
    }
}
