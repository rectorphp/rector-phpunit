<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\FixtureInnerClass;

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
