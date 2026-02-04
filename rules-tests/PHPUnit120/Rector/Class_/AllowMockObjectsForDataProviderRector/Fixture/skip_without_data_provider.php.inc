<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipWithoutDataProvider extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->expects($this->once())->method('some')->willReturn(true);
    }
}
