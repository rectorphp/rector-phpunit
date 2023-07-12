<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\AddProphecyTraitRector\Fixture;

use PHPUnit\Framework\TestCase;
use Prophecy\PhpUnit\ProphecyTrait;

final class SkipIfAlreadyAdded extends TestCase
{
    use ProphecyTrait;

    public function testOne(): void
    {
        $prophecy = $this->prophesize(\AnInterface::class);
    }
}
