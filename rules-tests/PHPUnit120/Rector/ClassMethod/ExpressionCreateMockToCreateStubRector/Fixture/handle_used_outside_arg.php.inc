<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class HandleUsedOutsideArg extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(\stdClass::class);

        if ($mock instanceof \stdClass) {
            // do something
        }

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class HandleUsedOutsideArg extends TestCase
{
    public function test()
    {
        $mock = $this->createStub(\stdClass::class);

        if ($mock instanceof \stdClass) {
            // do something
        }

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}

?>
