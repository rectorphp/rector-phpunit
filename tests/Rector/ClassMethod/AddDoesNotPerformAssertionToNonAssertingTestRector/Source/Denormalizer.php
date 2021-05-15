<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

final class Denormalizer
{
    public function __construct(private DenormalizerInterface $denormalizer)
    {
    }

    public function handle(array $data, string $type): ?array
    {
        try {
            return $this->denormalizer->denormalize($data, $type);
        } catch (\Throwable $throwable) {
            return null;
        }
    }
}
