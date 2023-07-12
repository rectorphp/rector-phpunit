<?php

namespace Rector\PHPUnit\Tests\PHPUnit80\Rector\MethodCall\SpecificAssertContainsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArrayMap extends TestCase
{
    public function test(array $items)
    {
        $mappedItems = array_map(function ($item) {
            return $item['value'];
        }, $items);

        $this->assertContains('foo', $mappedItems);
    }
}
