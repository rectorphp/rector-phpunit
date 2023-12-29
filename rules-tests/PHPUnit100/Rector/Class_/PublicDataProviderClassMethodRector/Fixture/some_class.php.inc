<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    protected function provideData()
    {
        yield [1];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
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
