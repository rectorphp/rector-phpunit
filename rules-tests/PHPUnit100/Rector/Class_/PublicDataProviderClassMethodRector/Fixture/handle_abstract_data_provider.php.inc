<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class HandleAbstractDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    protected abstract function provideData();
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class HandleAbstractDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    abstract public function provideData();
}

?>
