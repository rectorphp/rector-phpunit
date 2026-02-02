<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $mockObject = $this->createConfiguredMock(SomeEntityToBeConfigured::class, [
            'getName'=> 'John',
        ]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $mockObject = new \Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured();
        $mockObject->setName('John');
    }
}

?>
