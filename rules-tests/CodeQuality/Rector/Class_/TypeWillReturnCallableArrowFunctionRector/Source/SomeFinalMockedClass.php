<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source;

final class SomeFinalMockedClass
{
    public function anotherMethod(int $age): float
    {
        return 25.55;
    }
}
