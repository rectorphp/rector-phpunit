<?php

declare(strict_types=1);

namespace Rector\PHPUnit;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Stmt\Expression;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PhpDocParser\NodeTraverser\SimpleCallableNodeTraverser;

<<<<<<< HEAD
<<<<<<< HEAD
final readonly class MethodCallRemover
=======
final class MethodCallRemover
>>>>>>> 320f0bc (extract method call remoiver)
=======
final readonly class MethodCallRemover
>>>>>>> e2766a6 (single return stmt)
{
    public function __construct(
        private SimpleCallableNodeTraverser $simpleCallableNodeTraverser,
        private NodeNameResolver $nodeNameResolver
    ) {
    }

    public function removeMethodCall(Expression $expression, string $methodName): void
    {
        $this->simpleCallableNodeTraverser->traverseNodesWithCallable($expression, function (Node $node) use (
            $methodName
        ): ?Node {
            if (! $node instanceof MethodCall) {
                return null;
            }

            if (! $this->nodeNameResolver->isName($node->name, $methodName)) {
                return null;
            }

            return $node->var;
        });
    }
}
