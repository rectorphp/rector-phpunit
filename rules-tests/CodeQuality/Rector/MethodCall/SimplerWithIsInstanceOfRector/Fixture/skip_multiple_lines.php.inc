<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMultipleLines extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function ($args): bool {
                $this->assertCount(1, (array) $args);

                return $args instanceof \stdClass;
            }));
    }
}
