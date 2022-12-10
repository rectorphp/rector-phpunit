<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function testOne() {}
    public function testTwo() {}
    /**
     * @depends testOne
     * @depends testTwo
     */
    public function testThree(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function testOne() {}
    public function testTwo() {}
    #[\PHPUnit\Framework\Attributes\Depends('testOne')]
    #[\PHPUnit\Framework\Attributes\Depends('testTwo')]
    public function testThree(): void
    {
    }
}

?>
