<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipParameterUsed extends TestCase
{
    public function __construct($param)
    {
        $this->initEarly($param);
    }

    private function initEarly($param)
    {
        echo 'init';
    }
}
