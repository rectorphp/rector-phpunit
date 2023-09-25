<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleNonStaticMethodsInDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    public function provideData()
    {
        yield [$this->internalMethod()];
    }

    private function internalMethod()
    {
        return 1;
    }
}

?>
    -----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleNonStaticMethodsInDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [static::internalMethod()];
    }

    private static function internalMethod()
    {
        return 1;
    }
}

?>
