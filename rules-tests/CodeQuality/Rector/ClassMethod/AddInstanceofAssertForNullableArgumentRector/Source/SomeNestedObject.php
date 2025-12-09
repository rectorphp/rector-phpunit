<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source;

final class SomeNestedObject
{
    public function getNumber(): int
    {
        return 456;
    }
}
