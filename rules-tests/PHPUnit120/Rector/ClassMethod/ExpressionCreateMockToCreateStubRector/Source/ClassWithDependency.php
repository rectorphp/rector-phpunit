<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source;

final class ClassWithDependency
{
    public function __construct(
        private $dependency,
    ) {
    }

    public function getDependency()
    {
        return $this->dependency;
    }
}
