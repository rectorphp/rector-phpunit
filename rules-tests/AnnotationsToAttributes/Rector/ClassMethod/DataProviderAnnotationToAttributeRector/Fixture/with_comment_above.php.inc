<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

class WithCommentAbove extends \PHPUnit\Framework\TestCase
{
    /**
     * This is a useless test to demonstrate a problem.
     *
     * @dataProvider dataProvider
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

class WithCommentAbove extends \PHPUnit\Framework\TestCase
{
    /**
     * This is a useless test to demonstrate a problem.
     */
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
