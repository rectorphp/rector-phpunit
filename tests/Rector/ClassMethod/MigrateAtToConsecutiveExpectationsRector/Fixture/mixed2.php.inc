<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class Mixed2 extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock
            ->expects($this->exactly(2))
            ->method('someMethod');
        $mock
            ->expects($this->at(0))
            ->with(0)
            ->method('someMethod')
            ->willReturn('0');
        $mock
            ->expects($this->at(1))
            ->with(1)
            ->method('someMethod')
            ->willReturn('1');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class Mixed2 extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock
            ->expects($this->exactly(2))
            ->method('someMethod');
        $mock->method('someMethod')->withConsecutive([0], [1])->willReturnOnConsecutiveCalls('0', '1');
    }
}

?>
