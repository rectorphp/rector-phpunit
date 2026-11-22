<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArrayItemStoredInProperty extends TestCase
{
    private array $arguments;

    protected function setUp(): void
    {
        $this->arguments = [
            'item' => $this->createMock(\stdClass::class),
        ];

        $this->arguments['nested'] = [
            'item' => $this->createMock(\stdClass::class),
        ];
    }

    public function testThat()
    {
        ['item' => $item] = $this->arguments;

        $item->expects($this->once())->method('someMethod');
        $this->arguments['nested']['item']->expects($this->once())->method('someMethod');
    }
}
