<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\ValueObjectWithConstructor;

final class PassFloatToNullableString extends TestCase
{
    public function test()
    {
        $valueObject = new ValueObjectWithConstructor(123.456, '123');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\ValueObjectWithConstructor;

final class PassFloatToNullableString extends TestCase
{
    public function test()
    {
        $valueObject = new ValueObjectWithConstructor('123.456', 123);
    }
}

?>
