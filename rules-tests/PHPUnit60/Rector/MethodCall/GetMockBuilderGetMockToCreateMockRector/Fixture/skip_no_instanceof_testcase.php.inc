<?php

namespace Rector\Tests\PHPUnit\PHPUnit60\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector\Fixture;

class MockFactory
{
    public function __construct(protected \PHPUnit\Framework\TestCase $testCase)
    {
    }

    public function create(string $className): \PHPUnit\Framework\MockObject
    {
        return $this->getMockBuilder($className)->getMock();
    }

    protected function getMockBuilder(string $className): \PHPUnit\Framework\MockBuilder
    {
        return new \PHPUnit\Framework\MockBuilder($this->testCase, $className);
    }
}

?>
