<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Source\AbstractClassWithDataProvider;

final class RespectParentDataProvider extends AbstractClassWithDataProvider
{
    protected function provideData(): array
    {
        return [[1, 2]];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Source\AbstractClassWithDataProvider;

final class RespectParentDataProvider extends AbstractClassWithDataProvider
{
    public function provideData(): array
    {
        return [[1, 2]];
    }
}

?>
