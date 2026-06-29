<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\LazyContainer;

final class SkipPropertySelfReferencedInArrowFunction extends TestCase
{
    private LazyContainer $container;

    protected function setUp(): void
    {
        $this->container = new LazyContainer([
            'self' => fn (): LazyContainer => $this->container,
        ]);
    }

    public function test()
    {
        $this->assertTrue(true);
    }
}
