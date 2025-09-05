<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassToNullableString extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setMaybe(123456);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassToNullableString extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setMaybe('123456');
    }
}

?>
