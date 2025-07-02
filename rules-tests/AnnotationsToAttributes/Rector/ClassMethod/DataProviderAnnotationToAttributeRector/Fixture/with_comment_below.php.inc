<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

class WithCommentBelow extends \PHPUnit\Framework\TestCase
{
    /**
     * @dataProvider dataProvider
     *
     * This is a useless test to demonstrate a problem.
     */
    public function testProvider(bool $expected): void
    {
        self::assertSame($expected, $expected);
    }

    public static function dataProvider(): iterable
    {
        yield [true];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

class WithCommentBelow extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testProvider(bool $expected): void
    {
        self::assertSame($expected, $expected);
    }

    public static function dataProvider(): iterable
    {
        yield [true];
    }
}

?>
