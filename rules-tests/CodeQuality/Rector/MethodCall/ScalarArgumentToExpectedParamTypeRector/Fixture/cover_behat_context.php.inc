<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use Behat\Behat\Context\Context;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class CoverBehatContext implements Context
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

use Behat\Behat\Context\Context;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class CoverBehatContext implements Context
{
    public function test()
    {
        $someClassWithSetter = new SomeClassWithSetter();
        $someClassWithSetter->setItems('1', 2, '3', 4);
    }
}

?>
