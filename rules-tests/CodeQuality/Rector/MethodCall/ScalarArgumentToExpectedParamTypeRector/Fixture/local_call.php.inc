<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use Behat\Behat\Context\Context;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class LocalCall implements Context
{
    public function test()
    {
        $result = $this->sumUp('1', '2');
    }

    private function sumUp(int $a, int $b): int
    {
        return $a + $b;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use Behat\Behat\Context\Context;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class LocalCall implements Context
{
    public function test()
    {
        $result = $this->sumUp(1, 2);
    }

    private function sumUp(int $a, int $b): int
    {
        return $a + $b;
    }
}

?>
