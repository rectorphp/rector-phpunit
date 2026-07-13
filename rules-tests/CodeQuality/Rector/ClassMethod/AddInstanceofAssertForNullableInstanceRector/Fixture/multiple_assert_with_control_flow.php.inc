<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests;

final class MultipleAssertWithControlFlow extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertSame(1, $someObject->getSomeMethod());

        foreach ([1, 2, 3] as $item) {
            echo $item;
        }

        $someObject2 = $this->getSomeObject();
        $this->assertSame(2, $someObject2->getSomeMethod());
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

final class MultipleAssertWithControlFlow extends TestCase
{
    public function test(): void
    {
        $someObject = $this->getSomeObject();
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject);
        $this->assertSame(1, $someObject->getSomeMethod());

        foreach ([1, 2, 3] as $item) {
            echo $item;
        }

        $someObject2 = $this->getSomeObject();
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Source\SomeClassUsedInTests::class, $someObject2);
        $this->assertSame(2, $someObject2->getSomeMethod());
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
