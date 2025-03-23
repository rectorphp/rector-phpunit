<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveDataProviderParamKeysRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class KeepDatasetDescriptionTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $name): void
    {
    }

    public function provideData()
    {
        yield 'some description' => [
            'name' => 'Tom',
        ];
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveDataProviderParamKeysRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class KeepDatasetDescriptionTest extends TestCase
{
    #[DataProvider('provideData')]
    public function test(string $name): void
    {
    }

    public function provideData()
    {
        yield 'some description' => [
            'Tom',
        ];
    }
}

?>
