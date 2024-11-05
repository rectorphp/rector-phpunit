<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeTrait;

final class SkipUsedByTrait extends TestCase
{
    use SomeTrait;

    private bool $property;

    protected function setUp(): void
    {
    }

    public function test1()
    {
    }
}