<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubInCoalesceArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipInAssign extends TestCase
{
    public function testThat()
    {
        $value = mt_rand(0, 1);

        $result = $value ?? $this->createMock(\stdClass::class);
    }
}
