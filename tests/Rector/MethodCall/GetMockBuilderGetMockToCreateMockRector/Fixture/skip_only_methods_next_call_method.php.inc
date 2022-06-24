<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector\Fixture;

final class SkipOnlyMethodsNextCallMethod extends \PHPUnit\Framework\TestCase
{
    public function testDestructDoesNotThrowException()
     {
        $email = $this->getMockBuilder(Email::class)
            ->disableOriginalConstructor()
            ->onlyMethods(['sendCommand'])
            ->getMock();
         $email->method('sendCommand')
             ->willThrowException(new ErrorException('SMTP Error.'));
     }
}

