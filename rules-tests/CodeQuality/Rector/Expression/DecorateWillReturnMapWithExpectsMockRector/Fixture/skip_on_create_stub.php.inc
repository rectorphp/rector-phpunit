<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Source\SomeInterfaceToStub;

final class SkipOnCreateStub extends \PHPUnit\Framework\TestCase
{
    private SomeInterfaceToStub&Stub $service;

    protected function setUp(): void
    {
        $this->service = $this->createStub(SomeInterfaceToStub::class);
    }

    public function test()
    {
        $this->service->method('execute')->willReturnMap(['asdf', 'adsfasdf']);
        $this->service->execute();
    }
}
