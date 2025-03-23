<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveDataProviderParamKeysRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class SomeDataProviderWithYieldsTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $name): void
    {
    }

    public function provideData(): \Iterator
    {
        yield ['name' => 'Tom'];
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveDataProviderParamKeysRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class SomeDataProviderWithYieldsTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $name): void
    {
    }

    public function provideData(): \Iterator
    {
        yield ['Tom'];
    }
}

?>
