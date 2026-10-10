<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\AddProphecyTraitRector\Fixture;

final class SomeService
{
    public function run(): void
    {
        $prophecy = $this->prophesize(\AnInterface::class);
    }
}
