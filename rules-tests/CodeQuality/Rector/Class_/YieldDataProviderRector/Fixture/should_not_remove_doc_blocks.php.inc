<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class ShouldNotRemoveDocblocksTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $filePath): void
    {
    }

    public function provideData(): array
    {
        return [
            /**
             * @doto Yet another important comment
             */
            ['item1'],
            /**
             * @doto One final important comment
             */
            ['item2']
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class ShouldNotRemoveDocblocksTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $filePath): void
    {
    }

    public function provideData(): \Iterator
    {
        /**
         * @doto Yet another important comment
         */
        yield ['item1'];
        /**
         * @doto One final important comment
         */
        yield ['item2'];
    }
}

?>
