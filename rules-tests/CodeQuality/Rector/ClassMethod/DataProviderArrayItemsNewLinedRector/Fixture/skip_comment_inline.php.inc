<?php

namespace Rector\Tests\CodingStyle\Rector\ClassMethod\DataProviderArrayItemsNewlinedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipCommentInline extends TestCase
{
    /**
     * @dataProvider provideData()
     * @dataProvider provideData2()
     * @dataProvider provideData3()
     * @dataProvider provideData4()
     */
    public function testGetBytesSize(string $content, int $number): void
    {
        // ...
    }

    public function provideData(): array
    {
        return [
            ['content123', 11], // a comment inline
        ];
    }

    public function provideData2(): array
    {
        return [
            ['content123', 11], // a comment inline
            ['content123', 12],
        ];
    }

    public function provideData3(): array
    {
        return [
            ['content123', 11],
            ['content123', 12], // a comment inline
        ];
    }

    public function provideData4(): array
    {
        return [
            ['content123', 11], // a comment inline
            ['content123', 12], // a comment inline
        ];
    }
}