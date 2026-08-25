<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source;

final class SomeFactory
{
    public function create(): ?SomeClassUsedInTests
    {
        return null;
    }

    public function process(SomeClassUsedInTests $someClass): void
    {
    }
}
