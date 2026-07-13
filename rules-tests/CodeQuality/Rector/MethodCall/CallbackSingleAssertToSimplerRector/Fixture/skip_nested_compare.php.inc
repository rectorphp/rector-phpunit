<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\CallbackSingleAssertToSimplerRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNestedCompare extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->exactly(2))
            ->method('add')
            ->with($this->callback(function (array $args): bool {
                $this->assertSame($args['label'], 'Test Label');

                return true;
            }));
    }
}
