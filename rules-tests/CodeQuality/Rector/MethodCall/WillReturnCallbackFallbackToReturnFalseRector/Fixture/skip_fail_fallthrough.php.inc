<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipFailFallthrough extends TestCase
{
    public function test()
    {
        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->method('has')->willReturnCallback(function (string $id): bool {
            if ('service' === $id) {
                return true;
            }
            if ('other' === $id) {
                return false;
            }

            self::fail('Unknown ID requested: ' . $id);
        });
    }
}
