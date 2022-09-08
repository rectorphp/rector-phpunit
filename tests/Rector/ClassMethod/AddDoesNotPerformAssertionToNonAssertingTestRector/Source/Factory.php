<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

class Factory
{
    public function create(): \stdClass
    {
        return new \stdClass();
    }
}
