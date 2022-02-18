<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     */
    public function onePlusOneShouldBeTwo()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     */
    public function testOnePlusOneShouldBeTwo()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
