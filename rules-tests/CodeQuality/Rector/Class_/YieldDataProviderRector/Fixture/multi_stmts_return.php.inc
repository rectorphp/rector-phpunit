<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultiStmtsReturnTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): iterable
    {
        $a = 1;
        $b = 2;
        $c = 3;
        $d = 4;

        return [
            [$a, $b],
            [$c, $d]
        ];
    }

}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultiStmtsReturnTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): \Iterator
    {
        $a = 1;
        $b = 2;
        $c = 3;
        $d = 4;
        yield [$a, $b];
        yield [$c, $d];
    }

}

?>
