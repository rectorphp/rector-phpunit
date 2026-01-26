<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewlinedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipTestMethod extends TestCase
{
    public function test(): array
    {
        return [['content', 8], ['content123', 11]];
    }
}
