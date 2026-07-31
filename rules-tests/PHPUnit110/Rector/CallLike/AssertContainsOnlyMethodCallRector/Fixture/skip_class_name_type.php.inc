<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipClassNameType extends TestCase
{
    public function testMethod(): void
    {
        $this->assertContainsOnly(\stdClass::class, [new \stdClass()]);
        $this->assertContainsOnly('string', ['a'], false);
        $this->assertContainsOnly('string', ['a'], $isNativeType);
        $this->assertContainsOnly($type, ['a']);
    }
}
