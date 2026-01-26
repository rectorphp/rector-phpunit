<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PHPStan\PhpDoc\ResolvedPhpDocBlock;
use PHPStan\Reflection\ReflectionProvider;

final readonly class DoctrineEntityDocumentAnalyser
{
    /**
     * @var string[]
     */
    private const array ENTITY_DOCBLOCK_MARKERS = ['@Document', '@ORM\\Document', '@Entity', '@ORM\\Entity'];

    public function __construct(
        private ReflectionProvider $reflectionProvider,
    ) {
    }

    public function isEntityClass(string $className): bool
    {
        if (! $this->reflectionProvider->hasClass($className)) {
            return false;
        }

        $classReflection = $this->reflectionProvider->getClass($className);

        $resolvedPhpDocBlock = $classReflection->getResolvedPhpDoc();
        if (! $resolvedPhpDocBlock instanceof ResolvedPhpDocBlock) {
            return false;
        }

        foreach (self::ENTITY_DOCBLOCK_MARKERS as $entityDocBlockMarkers) {
            if (str_contains($resolvedPhpDocBlock->getPhpDocString(), $entityDocBlockMarkers)) {
                return true;
            }
        }

        // @todo apply attributes as well

        return false;
    }
}
