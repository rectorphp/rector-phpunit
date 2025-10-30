<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoArgs extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function (): bool {
                $args= [1, 2, 3];
                return count($args) === 5 && $args[0] === 'some_value';
            }));
    }
}
