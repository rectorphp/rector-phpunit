<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Source;

class ClassToStub
{
    public function foo(): string
    {
        return 'error';
    }
}