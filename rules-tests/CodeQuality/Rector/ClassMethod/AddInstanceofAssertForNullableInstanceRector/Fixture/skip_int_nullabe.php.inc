<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipIntNullable extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getValue();
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);
    }

    private function getValue(): ?int
    {
        if (mt_rand(0, 1)) {
            return 1000;
        }

        return null;
    }
}
