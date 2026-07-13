<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector\Source;

trait UsesMockPropertyTrait
{
    public function useMock(): void
    {
        $this->mockProperty->someMethod();
    }
}
