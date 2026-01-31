<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SomeTest extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(\stdClass::class);

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SomeTest extends TestCase
{
    public function test()
    {
        $mock = $this->createStub(\stdClass::class);

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}

?>
