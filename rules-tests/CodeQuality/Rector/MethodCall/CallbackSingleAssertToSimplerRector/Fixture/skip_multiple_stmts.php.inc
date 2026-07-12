<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\CallbackSingleAssertToSimplerRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMultipleStmts extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->exactly(2))
            ->method('add')
            ->with($this->callback(function ($type): bool {
                $this->assertSame(TextType::class, $type);
                $this->assertNotNull($type);

                return true;
            }));
    }
}
