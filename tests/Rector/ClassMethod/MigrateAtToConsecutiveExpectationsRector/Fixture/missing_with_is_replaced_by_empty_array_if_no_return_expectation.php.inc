<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class MissingWithIsReplacedByEmptyArrayIfNoReturnExpectation extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock
            ->expects($this->at(0))
            ->with('0')
            ->method('someMethod');
        $mock
            ->expects($this->at(2))
            ->with('2')
            ->method('someMethod');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class MissingWithIsReplacedByEmptyArrayIfNoReturnExpectation extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock->method('someMethod')->withConsecutive(['0'], [], ['2']);
    }
}

?>
