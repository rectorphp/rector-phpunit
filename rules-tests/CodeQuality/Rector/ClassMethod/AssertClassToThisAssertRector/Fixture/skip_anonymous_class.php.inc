<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class SkipAnonymousClass extends TestCase
{
    public function testMe()
    {
        $repository = new class() {
            public function getEntities(array $args = []): array
            {
                Assert::assertSame(['key' => 'value'], $args);

                return [];
            }
        };
    }
}
