<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArgumentStoredInProperty extends TestCase
{
    private $item;

    private array $items = [];

    public function testThat()
    {
        $this->setItem($this->createMock(\stdClass::class));

        $this->item->expects($this->once())->method('someMethod');
    }

    public function testVariadic()
    {
        $this->setItems($this->createMock(\stdClass::class), $this->createMock(\stdClass::class));

        $this->items[1]->expects($this->once())->method('someMethod');
    }

    public function testNamedArgument()
    {
        $this->setItemWithDefault(item: $this->createMock(\stdClass::class));

        $this->item->expects($this->once())->method('someMethod');
    }

    private function setItem($item): void
    {
        $this->item = $item;
    }

    private function setItemWithDefault($name = null, $item = null): void
    {
        $this->item = $item ?? new \stdClass();
    }

    private function setItems(...$items): void
    {
        $this->items = $items;
    }
}
