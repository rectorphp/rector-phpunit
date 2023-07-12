<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture\SomeClass;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder(SomeClass::class)
            ->setMethods(['run'])
            ->getMock();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture\SomeClass;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder(SomeClass::class)
            ->getMock();
    }
}

?>
