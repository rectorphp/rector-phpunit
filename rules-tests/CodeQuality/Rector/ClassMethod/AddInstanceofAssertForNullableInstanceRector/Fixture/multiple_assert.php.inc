<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class MultipleAssert extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);

        $someObject2 = $this->getSomeObject2();
        $value2 = $someObject2->getSomeMethod();

        $this->assertSame(123, $value2);
    }

    private function getSomeObject(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }

    private function getSomeObject2(): ?SomeClassUsedInTests
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

final class MultipleAssert extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertInstanceof(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject);
        $value = $someObject->getSomeMethod();

        $this->assertSame(123, $value);

        $someObject2 = $this->getSomeObject2();
        $this->assertInstanceof(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject2);
        $value2 = $someObject2->getSomeMethod();

        $this->assertSame(123, $value2);
    }

    private function getSomeObject(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }

    private function getSomeObject2(): ?SomeClassUsedInTests
    {
        if (mt_rand(0, 1)) {
            return new SomeClassUsedInTests();
        }

        return null;
    }
}

?>
