<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\CallbackSingleAssertToSimplerRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipReferencedUse extends TestCase
{
    public function test()
    {
        $download = null;

        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->once())
            ->method('detach')
            ->with($this->callback(function ($downloadDetach) use (&$download): bool {
                $this->assertSame($downloadDetach, $download);

                return true;
            }));
    }
}
