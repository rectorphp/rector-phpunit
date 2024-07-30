<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Fixture;

use CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Source\SomeService;
use PHPUnit\Framework\TestCase;

final class SkipOtherProperty extends TestCase
{
    private static $otherProperty;

    public static function setUpBeforeClass(): void
    {
        $someService = new SomeService();
    }
}
