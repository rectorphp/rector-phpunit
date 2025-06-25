<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MyTest2 extends TestCase
{
    public function test()
    {
        $this->assertTrue(\array_search($foo, $this->bar->toArray()));
        $this->assertNotFalse(\array_search($foo, $this->bar->toArray()));
    }
}

?>
