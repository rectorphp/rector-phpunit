<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Source;

use PHPUnit\Framework\TestCase;

abstract class TestResponse extends TestCase
{
    public function __construct()
    {
        echo "init";
    }
}
