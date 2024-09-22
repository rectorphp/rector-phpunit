<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipThisLocal extends TestCase
{
    public function testMe()
    {
        $values = $this->getValues();
    }

    public function getValues()
    {
        return [1, 2, 3];
    }
}
