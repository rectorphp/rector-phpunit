<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\RemoveNamedArgsInDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ProvideDataWithSeveralNamedAndNotNamedArgs extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [
            'namedArg' => 100,
            null,
            fn() => 'G-EASY',
            'Key' => fn() => 'Post Malone',
            'another' => 'arg1',
            new \Exception(),
            true,
            'false' => false
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\RemoveNamedArgsInDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ProvideDataWithSeveralNamedAndNotNamedArgs extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [
            100,
            null,
            fn() => 'G-EASY',
            fn() => 'Post Malone',
            'arg1',
            new \Exception(),
            true,
            false
        ];
    }
}

?>
