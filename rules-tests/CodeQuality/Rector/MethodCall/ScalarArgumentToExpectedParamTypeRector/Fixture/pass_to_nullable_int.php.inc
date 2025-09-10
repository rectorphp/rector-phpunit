<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassToNullableInt extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setValue('letter', '123456');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\NullableSetter;

final class PassToNullableInt extends TestCase
{
    public function test()
    {
        $nullableSetter = new NullableSetter();
        $nullableSetter->setValue('letter', 123456);
    }
}

?>
