<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MixingArrays extends TestCase
{
    public function barTest()
    {
        $this->mocks[Myclass::class]->expects($this->at(0))->method('sasa')->willReturn([
            (new Myclass(new Myclass($winner, new Myclass(2), Myclass::getStandard())))->setUser1Result(Myclass::getByCode(Myclass::WIN))
        ]);
    }
}
