<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source\AbstractEntityToBeConfigured;

final class SkipAbstractEntity extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $mockObject = $this->createConfiguredMock(AbstractEntityToBeConfigured::class, [
            'getName'=> 'John',
        ]);
    }
}
