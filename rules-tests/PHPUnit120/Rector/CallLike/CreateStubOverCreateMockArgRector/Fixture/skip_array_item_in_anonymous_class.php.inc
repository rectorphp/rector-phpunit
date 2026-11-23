<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArrayItemInAnonymousClass extends TestCase
{
    public function testThat()
    {
        $factory = new class {
            public function build(): array
            {
                return [$this->createMock('item')];
            }

            private function createMock(string $name): string
            {
                return $name;
            }
        };

        $this->assertSame(['item'], $factory->build());
    }
}
