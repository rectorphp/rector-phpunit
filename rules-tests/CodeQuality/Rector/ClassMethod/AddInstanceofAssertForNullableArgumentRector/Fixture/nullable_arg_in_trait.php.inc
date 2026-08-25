<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source\SomeFactory;

trait NullableArgInTrait
{
    public function assertSomething(SomeFactory $someFactory): void
    {
        $someObject = $someFactory->create();

        $someFactory->process($someObject);
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source\SomeFactory;

trait NullableArgInTrait
{
    public function assertSomething(SomeFactory $someFactory): void
    {
        $someObject = $someFactory->create();
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableArgumentRector\Source\SomeClassUsedInTests::class, $someObject);

        $someFactory->process($someObject);
    }
}

?>
