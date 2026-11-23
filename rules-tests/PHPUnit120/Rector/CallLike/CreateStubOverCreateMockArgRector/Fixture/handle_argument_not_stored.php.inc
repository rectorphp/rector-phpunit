<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArgumentNotStored extends TestCase
{
    public function testThat()
    {
        $this->useItem($this->createMock(\stdClass::class));

        $service = new ServiceWithItem($this->createMock(\stdClass::class));
        $service->setItem($this->createMock(\stdClass::class));
        ServiceWithItem::create($this->createMock(\stdClass::class));
    }

    private function useItem($item): void
    {
        $this->assertInstanceOf(\stdClass::class, $item);
    }
}

final class ServiceWithItem
{
    private $item;

    public function __construct($item)
    {
        $this->item = $item;
    }

    public function setItem($item): void
    {
        $this->item = $item;
    }

    public static function create($item): self
    {
        $self = new self(null);
        $self->item = $item;

        return $self;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArgumentNotStored extends TestCase
{
    public function testThat()
    {
        $this->useItem($this->createStub(\stdClass::class));

        $service = new ServiceWithItem($this->createStub(\stdClass::class));
        $service->setItem($this->createStub(\stdClass::class));
        ServiceWithItem::create($this->createStub(\stdClass::class));
    }

    private function useItem($item): void
    {
        $this->assertInstanceOf(\stdClass::class, $item);
    }
}

final class ServiceWithItem
{
    private $item;

    public function __construct($item)
    {
        $this->item = $item;
    }

    public function setItem($item): void
    {
        $this->item = $item;
    }

    public static function create($item): self
    {
        $self = new self(null);
        $self->item = $item;

        return $self;
    }
}

?>
