<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\FixtureInnerClass;

use PHPUnit\Framework\TestCase;

final class MyTest extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
        new class() extends \stdClass {
            public function __construct()
            {
            }
        };
    }
}
