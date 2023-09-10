<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Source\TestResponse;

final class SkipCallParentConstruct extends TestResponse
{
    private $someValue;

    /**
     * some comments
     */
    public function __construct(?string $name = null, array $data = [], string $dataName = '')
    {
        $this->someValue = 1000;
        parent::__construct($name, $data, $dataName);
    }
}
