<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\ParentTestClassConstructorRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAlreadyAdded extends TestCase
{
    public function __construct()
    {
        parent::__construct(static::class);
    }
}
