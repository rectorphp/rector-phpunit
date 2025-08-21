<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source;

// non final on purpose so PHPStan can analyze it
class SomeMockedClass
{
    public function someMethod(string $name): int
    {
        return 100;
    }

    public function nativeObject(object $object): object
    {
        return $object;
    }
}
