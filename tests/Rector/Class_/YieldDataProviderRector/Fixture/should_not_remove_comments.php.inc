<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ShouldNotRemoveComments extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
    }

    public function provideData(): array
    {
        // Let's pretend that this comment is extremely important and meaningful.
        // It should not be removed by Rector.
        return [
            // This is yet another comment.
            ['item1'],

            // And a final one.
            ['item2'],
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ShouldNotRemoveComments extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
    }

    public function provideData(): \Iterator
    {
        // This is yet another comment.
        yield ['item1'];
        // And a final one.
        yield ['item2'];
    }
}

?>
