<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PHPStan\PhpDoc\ResolvedPhpDocBlock;
use PHPStan\Reflection\ClassReflection;

final readonly class DoctrineEntityDocumentAnalyser
{
    /**
     * @var string[]
     */
    private const array ENTITY_DOCBLOCK_MARKERS = ['@Document', '@ORM\\Document', '@Entity', '@ORM\\Entity'];

    public function isEntityClass(ClassReflection $classReflection): bool
    {
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
