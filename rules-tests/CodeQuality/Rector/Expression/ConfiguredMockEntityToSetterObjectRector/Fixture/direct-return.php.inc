<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured;

final class DirectReturn extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        return $this->createConfiguredMock(SomeEntityToBeConfigured::class, [
            'getName'=> 'John',
        ]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured;

final class DirectReturn extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someEntityToBeConfigured = new \Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeEntityToBeConfigured();
        $someEntityToBeConfigured->setName('John');
        return $someEntityToBeConfigured;
    }
}

?>
