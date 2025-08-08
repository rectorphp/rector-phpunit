<?php

namespace Rector\PHPUnit\Tests\Issues\AnnotationParsing\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(?bool $param1, string $param2, bool $param3)
    {
        $this->assertTrue($param1);
        $this->assertSame('string', $param2);
        $this->assertTrue($param3);
    }

    /**
     * @return array<array{0: bool|null, 1: string, 2: bool}>
     */
    public static function dataProvider(): array
    {
        return [
            'data1' => [null, 'string', false],
            'data2' => [false, 'string', false],
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Issues\AnnotationParsing\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(?bool $param1, string $param2, bool $param3)
    {
        $this->assertTrue($param1);
        $this->assertSame('string', $param2);
        $this->assertTrue($param3);
    }

    /**
     * @return \Iterator<(int | string), array{(bool | null), string, bool}>
     */
    public static function dataProvider(): \Iterator
    {
        yield 'data1' => [null, 'string', false];
        yield 'data2' => [false, 'string', false];
    }
}

?>
