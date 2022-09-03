<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

final class CachedAdapter
{
    public function __construct(private CacheInterface $cache)
    {
    }

    public function delete($key): bool
    {
        return $this->cache->delete($key);
    }
}
