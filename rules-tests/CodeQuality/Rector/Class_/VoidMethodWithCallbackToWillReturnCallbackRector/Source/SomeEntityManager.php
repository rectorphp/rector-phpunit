<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source;

// non final on purpose so PHPStan can analyze it
class SomeEntityManager
{
    public function persist(object $entity): void
    {
    }

    public function count(string $name): int
    {
        return 100;
    }
}
