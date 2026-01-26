<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewlinedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoArray extends TestCase
{
    public function provideData(): array
    {
        return 'content' . 8;
    }
}
