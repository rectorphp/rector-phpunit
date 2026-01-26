<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass;

final class SkipIfAssert extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(AnotherClass::class);

        $anotherClass = new AnotherClass(1, 2, 3, $someMock);

        $this->assertSame($someMock, $anotherClass->getSomeMock());
    }
}
