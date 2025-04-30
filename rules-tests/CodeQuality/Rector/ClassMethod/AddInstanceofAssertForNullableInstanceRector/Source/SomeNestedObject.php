<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source;

final class SomeNestedObject
{
    public function getNumber(): int
    {
        return 456;
    }
}
