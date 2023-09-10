<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Source\TestResponse;

final class SkipCallParentConstruct extends TestResponse
{
    private $someValue;

    public function __construct()
    {
        $this->someValue = 1000;

        parent::__construct();
    }
}
