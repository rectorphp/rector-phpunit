<?php

namespace PHPUnit\Framework;

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

class TestCase
{
}

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

abstract class AbstractFooTestCase extends TestCase
{
    /**
     * @dataProvider dataProvider
     */
    public function testWithDataProvider($value1, $value2): void
    {
        
    }
    
    abstract public function dataProvider(): array;
}

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

class MyTest extends AbstractFooTestCase
{
    public function dataProvider(): array
    {
        return [
        	[1, 2],
        ];
    }
}

?>
-----
<?php

namespace PHPUnit\Framework;

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

class TestCase
{
}

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

abstract class AbstractFooTestCase extends TestCase
{
    /**
     * @dataProvider dataProvider
     */
    public function testWithDataProvider($value1, $value2): void
    {
        
    }
    
    abstract public static function dataProvider(): array;
}

namespace Rector\Tests\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

class MyTest extends AbstractFooTestCase
{
    public static function dataProvider(): array
    {
        return [
        	[1, 2],
        ];
    }
}

?>
