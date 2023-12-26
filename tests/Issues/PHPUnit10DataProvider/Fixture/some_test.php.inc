<?php

namespace Rector\PHPUnit\Tests\Issues\PHPUnit10DataProvider\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
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

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('fooProvider')]
    #[\PHPUnit\Framework\Attributes\Test]
    public function it_should_do_stuff(string $foo): void
    {
    }

    public static function fooProvider(): array
    {
        return [];
    }
}

?>
