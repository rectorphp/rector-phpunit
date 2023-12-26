<?php

namespace Rector\PHPUnit\Tests\Issues\PHPUnit10DataProvider\Fixture;

final class SomeTest
{
    /**
     * @test
     * @dataProvider fooProvider
     */
    public function it_should_do_stuff(string $foo): void
    {
    }

    public static function fooProvider(): array
    {
        return [];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Issues\PHPUnit10DataProvider\Fixture;

final class SomeTest
{
    #[\PHPUnit\Framework\Attributes\Test]
    #[\PHPUnit\Framework\Attributes\DataProvider('fooProvider')]
    public function it_should_do_stuff(string $foo): void
    {
    }

    public static function fooProvider(): array
    {
        return [];
    }
}

?>
