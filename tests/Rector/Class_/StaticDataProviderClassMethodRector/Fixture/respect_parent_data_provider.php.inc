<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Source\AbstractClassWithDataProvider;

final class RespectParentDataProvider extends AbstractClassWithDataProvider
{
    public function provideData(): array
    {
        return [[1, 2]];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Source\AbstractClassWithDataProvider;

final class RespectParentDataProvider extends AbstractClassWithDataProvider
{
    public static function provideData(): array
    {
        return [[1, 2]];
    }
}

?>
