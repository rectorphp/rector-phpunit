<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source\SomeClassUsedInTests;

final class SkipAssertPass extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertInstanceOf(\stdClass::class, $someObject);
    }

    private function getSomeObject(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }
}
