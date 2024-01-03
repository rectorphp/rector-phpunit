<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PhpDoc;

use PhpParser\Node\Expr;
use PhpParser\Node\Name;
use PhpParser\Node\Scalar\String_;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\Reflection\ReflectionProvider;
use Rector\PhpParser\Node\NodeFactory;

final readonly class PhpDocValueToNodeMapper
{
    public function __construct(
        private NodeFactory $nodeFactory,
        private ReflectionProvider $reflectionProvider
    ) {
    }

    public function mapGenericTagValueNode(GenericTagValueNode $genericTagValueNode): Expr
    {
        if (\str_contains($genericTagValueNode->value, '::')) {
            [$class, $constant] = explode('::', $genericTagValueNode->value);

            $name = new Name($class);
            return $this->nodeFactory->createClassConstFetchFromName($name, $constant);
        }

        $reference = ltrim($genericTagValueNode->value, '\\');

        if ($this->reflectionProvider->hasClass($reference)) {
            return $this->nodeFactory->createClassConstReference($reference);
        }

        return new String_($reference);
    }
}
