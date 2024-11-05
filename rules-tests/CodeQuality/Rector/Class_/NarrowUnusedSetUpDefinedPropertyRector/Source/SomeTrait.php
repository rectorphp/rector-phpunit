<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source;

trait SomeTrait
{
    public function init()
    {
        // some complex check
        $this->property = true;

        $this->assertTrue($this->property);
    }
}
