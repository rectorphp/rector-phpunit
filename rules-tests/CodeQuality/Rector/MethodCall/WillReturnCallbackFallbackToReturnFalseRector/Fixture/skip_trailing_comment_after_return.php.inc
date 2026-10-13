<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipTrailingCommentAfterReturn extends TestCase
{
    public function test()
    {
        $callSequence = [];

        $queueMock = $this->createMock(\stdClass::class);
        $queueMock->expects($this->atLeastOnce())->method('isEmpty')->willReturnCallback(static function () use (&$callSequence): bool {
            $callSequence[] = 'isEmpty';

            return true; // Exit loop immediately
        });
    }
}
