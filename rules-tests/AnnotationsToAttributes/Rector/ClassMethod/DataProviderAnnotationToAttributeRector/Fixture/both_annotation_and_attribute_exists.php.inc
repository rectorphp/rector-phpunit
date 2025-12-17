<?php

declare(strict_types=1);

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class BothAnnotationAndAttributeExists extends TestCase
{
    /** @dataProvider provideData */
    #[DataProvider('provideData')]
    public function testExample(string $value): void
    {
        self::assertNotEmpty($value);
    }

    public static function provideData(): iterable
    {
        yield 'case 1' => ['foo'];
        yield 'case 2' => ['bar'];
    }
}

?>
-----
<?php

declare(strict_types=1);

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class BothAnnotationAndAttributeExists extends TestCase
{
    #[DataProvider('provideData')]
    public function testExample(string $value): void
    {
        self::assertNotEmpty($value);
    }

    public static function provideData(): iterable
    {
        yield 'case 1' => ['foo'];
        yield 'case 2' => ['bar'];
    }
}

?>