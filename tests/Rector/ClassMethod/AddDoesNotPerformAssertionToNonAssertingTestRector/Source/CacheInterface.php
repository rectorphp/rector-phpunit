<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

interface CacheInterface
{
    public function has(): bool;
    public function delete($key): bool;
}
