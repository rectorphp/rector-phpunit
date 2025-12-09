<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source;

final class SomeClassUsedInTests
{
    public function getSomeMethod(): int
    {
         return 1000;
    }

    public function getSomeNestedObject(): ?SomeNestedObject
    {
        return new SomeNestedObject();
    }
}
