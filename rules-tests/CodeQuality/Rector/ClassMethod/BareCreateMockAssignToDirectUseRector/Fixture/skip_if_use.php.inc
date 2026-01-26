<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass;

final class SkipIfUse extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(AnotherClass::class);

        $someClosure = function() use ($someMock) {
            // some logic here

            return $someMock;
        };
    }
}
