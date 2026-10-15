<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipThrowAfterBoolReturns extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);

        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->expects($matcher)->method('checkContext')->willReturnCallback(function (string $id) use ($matcher) {
            if ($id === 'service') {
                return true;
            }

            if ($id === 'other') {
                return false;
            }

            throw new \Exception();
        });
    }
}
