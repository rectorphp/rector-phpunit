<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

final class SkipGenerator extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $executedProcesses = $this->get();
        $this->assertSame(10, iterator_count($executedProcesses));
    }

    private function get(): \Generator
    {
        for ($i = 0; $i < 10; $i++) {
            yield $i;
        }
    }
}
