<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithEqualToRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDifferentAssert extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->exactly(2))
            ->method('add')
            ->with($this->callback(function ($type): bool {
                $this->assertInstanceOf(TextType::class, $type);

                return true;
            }));
    }
}
