<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoverNoBracketName extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    public function provideData()
    {
        yield [1];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoverNoBracketName extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [1];
    }
}

?>
