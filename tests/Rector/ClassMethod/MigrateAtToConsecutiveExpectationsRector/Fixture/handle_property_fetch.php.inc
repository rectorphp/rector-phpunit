<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class HandlePropertyFetch extends \PHPUnit\Framework\TestCase
{
    protected $mock;

    protected function setUp(): void
    {
        parent::setUp();

        $this->mock = $this->createMock(SomeObject::class);
    }

    public function test(): void
    {
        $this->mock
            ->expects($this->at(0))
            ->method('someMethod')
            ->willReturn(1);

        $this->mock
            ->expects($this->at(1))
            ->method('someMethod')
            ->willReturn(2);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class HandlePropertyFetch extends \PHPUnit\Framework\TestCase
{
    protected $mock;

    protected function setUp(): void
    {
        parent::setUp();

        $this->mock = $this->createMock(SomeObject::class);
    }

    public function test(): void
    {
        $this->mock->method('someMethod')->willReturnOnConsecutiveCalls(1, 2);
    }
}

?>
