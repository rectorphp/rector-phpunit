<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Source\AnyBook;

class UnionTypeMock extends TestCase
{
    private MockObject|AnyBook $anyBook;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Source\AnyBook;

class UnionTypeMock extends TestCase
{
    private MockObject $anyBook;
}

?>
