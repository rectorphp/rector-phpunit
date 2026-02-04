<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveStandaloneCreateMockRector\Fixture;

final class SkipAssignedCall extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
        $value = $this->createMock('someClass');
    }
}
