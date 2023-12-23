<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector\Fixture;

class SkipOutsideCall
{
    public function test(\PHPUnit\Framework\TestCase $testCase)
    {
        $mockedObject = $testCase->getMockBuilder('someType')
            ->disableOriginalConstructor()
            ->getMock();
    }
}
