<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassFloatToNullableString extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setMaybe(123.456);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassFloatToNullableString extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setMaybe('123.456');
    }
}

?>
