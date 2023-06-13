<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\YieldDataProviderRector\Fixture;

final class SkipNonTestCase
{
    public static function provideData()
    {
        return [
            ['<?php implode("", $foo, );', '<?php implode($foo, "", );']
        ];
    }
}
