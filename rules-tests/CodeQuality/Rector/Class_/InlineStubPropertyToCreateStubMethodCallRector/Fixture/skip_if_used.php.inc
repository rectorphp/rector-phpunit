<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class SkipIfUsed extends TestCase
{
    private Stub $someStub;

    protected function setUp(): void
    {
        $this->someStub = $this->createStub(NotRelevantClass::class);
    }

    public function testAnother()
    {
        $someCall = $this->someStub->method('some_method');

        $anotherObject = new NotRelevantClass($this->someStub);
    }
}
