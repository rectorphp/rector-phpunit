<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class HandleAbstractDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    public abstract function provideData();
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class HandleAbstractDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    abstract public static function provideData();
}

?>
