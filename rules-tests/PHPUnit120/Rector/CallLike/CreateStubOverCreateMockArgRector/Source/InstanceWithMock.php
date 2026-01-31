<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source;

final class InstanceWithMock
{
    public function __construct(private $object)
    {
    }

    public function getInner(): object
    {
        return $this->object;
    }
}
