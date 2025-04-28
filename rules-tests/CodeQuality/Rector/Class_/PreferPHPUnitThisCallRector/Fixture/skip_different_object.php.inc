<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDifferentObjectType extends TestCase
{
    public function testMe()
    {
        $someMock = $object->execute()::createMock('stdClass');
    }
}
