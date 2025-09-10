<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source;

final class ValueObjectWithConstructor
{
    public function __construct(?string $letter, ?int $number = null)
    {
    }
}
