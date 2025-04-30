<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class DoubleInstanceOrder extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $someNestedObject = $someObject->getSomeNestedObject();

        $this->assertSame(123, $someNestedObject->getNumber());
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

final class DoubleInstanceOrder extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject);
        $someNestedObject = $someObject->getSomeNestedObject();
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeNestedObject::class, $someNestedObject);

        $this->assertSame(123, $someNestedObject->getNumber());
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
