<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewlinedRector\Fixture;

final class SkipNonPhpUnit
{
    public function provideData(): array
    {
        return [['content', 8], ['content123', 11]];
    }
}
