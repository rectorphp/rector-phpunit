<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\ExceptionAnnotationRector\Fixture;

final class MyTest extends \PHPUnit_Framework_TestCase
{
    /**
     * @expectedException \FooException
     */
    public function test()
    {
        // some code

    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\ExceptionAnnotationRector\Fixture;

final class MyTest extends \PHPUnit_Framework_TestCase
{
    public function test()
    {
        $this->expectException('FooException');
        // some code

    }
}

?>
