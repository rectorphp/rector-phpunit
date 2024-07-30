<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Fixture;

use CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Source\SomeService;
use PHPUnit\Framework\TestCase;

final class KeepUnrelatedMethod extends TestCase
{
    private static $someService;

    public static function prepare(): void
    {
        self::$someService = new SomeService();
    }

    public function test()
    {
        $result = self::$someService->getValue();
    }
}
