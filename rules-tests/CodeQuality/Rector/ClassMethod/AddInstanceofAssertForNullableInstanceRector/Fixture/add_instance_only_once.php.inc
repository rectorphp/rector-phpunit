<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class AddInstanceOnlyOnce extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);

        // we know the value here, no need to add instanceof
        $value = $someObject->getSomeMethod();
    }

    private function getSomeObject(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class AddInstanceOnlyOnce extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertInstanceof(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject);
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);

        // we know the value here, no need to add instanceof
        $value = $someObject->getSomeMethod();
    }

    private function getSomeObject(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }
}

?>
