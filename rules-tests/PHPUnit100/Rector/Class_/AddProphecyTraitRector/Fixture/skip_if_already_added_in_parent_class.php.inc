<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\AddProphecyTraitRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\AddProphecyTraitRector\Source\ParentClassWithPropertyTrait;

final class SkipIfAlreadyAddedInParentClass extends ParentClassWithPropertyTrait
{
    public function test(): void
    {
        $prophecy = $this->prophesize(\AnInterface::class);
    }
}
