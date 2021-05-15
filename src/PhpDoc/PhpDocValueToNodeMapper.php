<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PhpDoc;

use Nette\Utils\Strings;
use PhpParser\Node\Expr;
use PhpParser\Node\Scalar\String_;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\Reflection\ReflectionProvider;
use Rector\Core\PhpParser\Node\NodeFactory;

final class PhpDocValueToNodeMapper
{
    public function __construct(
        private NodeFactory $nodeFactory,
        private ReflectionProvider $reflectionProvider
    ) {
    }

    public function mapGenericTagValueNode(GenericTagValueNode $genericTagValueNode): Expr
    {
        if (Strings::contains($genericTagValueNode->value, '::')) {
            [$class, $constant] = explode('::', $genericTagValueNode->value);
            return $this->nodeFactory->createShortClassConstFetch($class, $constant);
        }

        $reference = ltrim($genericTagValueNode->value, '\\');

        if ($this->reflectionProvider->hasClass($reference)) {
            return $this->nodeFactory->createClassConstReference($reference);
        }

        return new String_($reference);
    }
}
