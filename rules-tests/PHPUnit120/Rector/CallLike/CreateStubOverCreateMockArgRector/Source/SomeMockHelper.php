<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source;

use DateTime;
use PHPUnit\Framework\MockObject\MockObject;

class SomeMockHelper {
    public function __construct(
    	public MockObject&DateTime $i
    ) {}

    public function configureMock(array $data): void
    {
    }
}