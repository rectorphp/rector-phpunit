<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class MultipleArgs extends TestCase
{
    public function test()
    {
        $someClassWithSetter = new SomeClassWithSetter();
        $someClassWithSetter->setItems('1', 2, 3, 4);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class MultipleArgs extends TestCase
{
    public function test()
    {
        $someClassWithSetter = new SomeClassWithSetter();
        $someClassWithSetter->setItems('1', 2, '3', 4);
    }
}

?>
