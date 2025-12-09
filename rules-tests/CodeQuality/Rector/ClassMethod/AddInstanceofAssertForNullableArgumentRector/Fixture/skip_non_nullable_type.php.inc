<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source\SomeClassUsedInTests;

final class SkipNonNullableType extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();

        $this->process($someObject);
    }

    private function getSomeObject(): SomeClassUsedInTests
    {
        return new SomeClassUsedInTests();
    }

    private function process(SomeClassUsedInTests $someObject)
    {
    }
}
