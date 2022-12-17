<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Source\AnotherTest;

class DependsOnClass extends \PHPUnit\Framework\TestCase
{
    /**
     * @depends AnotherTest::class
     */
    public function test(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Source\AnotherTest;

class DependsOnClass extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DependsOnClass(AnotherTest::class)]
    public function test(): void
    {
    }
}

?>
