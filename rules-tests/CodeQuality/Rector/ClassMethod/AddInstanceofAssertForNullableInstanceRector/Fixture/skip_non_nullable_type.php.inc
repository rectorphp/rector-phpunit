<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class SkipNonNullableType extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);
    }

    private function getSomeObject(): SomeClassUsedInTests
    {
        return new SomeClassUsedInTests();
    }
}
