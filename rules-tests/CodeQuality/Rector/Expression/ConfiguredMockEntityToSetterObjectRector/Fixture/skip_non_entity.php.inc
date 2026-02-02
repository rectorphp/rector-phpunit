<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\SomeObjectToBeConfigured;

final class SkipNonEntity extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $mockObject = $this->createConfiguredMock(SomeObjectToBeConfigured::class, [
            'getName'=> 'John',
        ]);
    }
}
