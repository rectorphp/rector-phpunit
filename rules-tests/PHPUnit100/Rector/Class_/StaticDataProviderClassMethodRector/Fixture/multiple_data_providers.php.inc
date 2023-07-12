<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleDataProviders extends TestCase
{
    /**
     * @dataProvider provideData
     * @dataProvider provideMoreData()
     */
    public function test()
    {
    }

    public function provideData()
    {
        yield [1];
    }

    public function provideMoreData()
    {
        yield [1];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleDataProviders extends TestCase
{
    /**
     * @dataProvider provideData
     * @dataProvider provideMoreData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [1];
    }

    public static function provideMoreData()
    {
        yield [1];
    }
}

?>
