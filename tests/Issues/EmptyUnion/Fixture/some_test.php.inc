<?php

namespace Rector\PHPUnit\Tests\Issues\EmptyUnion\Fixture;

use ArrayIterator;
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function testSomething()
    {
        $this->assertCount(0, $this->someCall());
    }

    public function someCall(): ?ArrayIterator
    {
        return new ArrayIterator([]);
    }
}
