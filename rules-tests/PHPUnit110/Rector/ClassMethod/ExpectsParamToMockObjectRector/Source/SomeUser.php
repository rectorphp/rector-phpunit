<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source;

final class SomeUser
{
    public function getId(): int
    {
        return 1;
    }
}
