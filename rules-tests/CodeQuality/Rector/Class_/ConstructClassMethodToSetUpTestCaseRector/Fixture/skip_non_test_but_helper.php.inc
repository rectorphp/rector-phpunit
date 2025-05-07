<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonTestButHelper extends TestCase
{
    private $someValue;

    public function __construct()
    {
        $this->someValue = 1000;
    }
}
