<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use DateTime;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source\SomeMockHelper;

class SkipAsArgumentWithMockObjectType extends TestCase {
    public function testFoo(): void
    {
        new SomeMockHelper($this->createMock(DateTime::class));
    }
}
