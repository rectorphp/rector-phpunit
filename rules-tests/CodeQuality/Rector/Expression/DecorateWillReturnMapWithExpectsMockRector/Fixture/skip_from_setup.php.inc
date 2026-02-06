<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SkipFromSetup extends \PHPUnit\Framework\TestCase
{
    protected function setUp(): void
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturnMap([1, 2]);
    }
}
