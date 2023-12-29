<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

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

    protected function provideData()
    {
        yield [1];
    }

    protected function provideMoreData()
    {
        yield [1];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

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
