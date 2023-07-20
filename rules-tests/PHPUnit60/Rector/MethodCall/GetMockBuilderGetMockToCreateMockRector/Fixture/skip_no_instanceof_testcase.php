<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector\Fixture;

final class SkipNoInstanceofTestCase
{
    public function __construct(protected \PHPUnit\Framework\TestCase $testCase)
    {
    }

    public function create(string $className): \PHPUnit\Framework\MockObject\MockObject
    {
        return $this->getMockBuilder($className)->getMock();
    }

    protected function getMockBuilder(string $className): \PHPUnit\Framework\MockObject\MockBuilder
    {
        return new \PHPUnit\Framework\MockObject\MockBuilder($this->testCase, $className);
    }
}
