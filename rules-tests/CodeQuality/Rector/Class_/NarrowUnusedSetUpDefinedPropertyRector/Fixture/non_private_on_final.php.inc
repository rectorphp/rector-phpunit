<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class NonPrivateOnFinalClass extends TestCase
{
    protected SomeType $someMock;

    protected function setUp(): void
    {
        $this->someMock = new SomeType();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class NonPrivateOnFinalClass extends TestCase
{
    protected function setUp(): void
    {
        $someMock = new SomeType();
    }
}

?>
