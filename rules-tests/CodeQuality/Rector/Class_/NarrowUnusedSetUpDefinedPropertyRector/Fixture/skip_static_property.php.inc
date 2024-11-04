<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class SkipStaticPrpoerty extends TestCase
{
    private static SomeType $someMock;

    protected function setUp(): void
    {
        self::$someMock = new SomeType();
    }
}
