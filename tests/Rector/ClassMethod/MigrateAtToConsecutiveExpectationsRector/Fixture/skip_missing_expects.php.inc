<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

class Foo
{
    public function someMethod()
    {
    }
}
final class SkipMissingExpects extends \PHPUnit\Framework\TestCase
{
    protected $mock;

    protected function setUp(): void
    {
        parent::setUp();

        $this->mock = $this->createMock(Foo::class);
    }

    public function test(): void
    {
        $this->mock
            ->method('someMethod')
            ->willReturn(1);

        $mock = $this->createMock(Foo::class);

        $mock
            ->method('someOtherMethod')
            ->willReturn(1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

class Foo
{
    public function someMethod()
    {
    }
}
final class SkipMissingExpects extends \PHPUnit\Framework\TestCase
{
    protected $mock;

    protected function setUp(): void
    {
        parent::setUp();

        $this->mock = $this->createMock(Foo::class);
    }

    public function test(): void
    {
        $this->mock
            ->method('someMethod')
            ->willReturn(1);

        $mock = $this->createMock(Foo::class);

        $mock
            ->method('someOtherMethod')
            ->willReturn(1);
    }
}

?>
