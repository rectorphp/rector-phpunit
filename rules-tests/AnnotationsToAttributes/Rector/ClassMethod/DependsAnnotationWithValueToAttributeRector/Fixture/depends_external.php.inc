<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

use Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Source\AnotherTest;

class DependsExternal extends \PHPUnit\Framework\TestCase
{
    /**
     * @depends AnotherTest::testMethod
     */
    public function test(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

use Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Source\AnotherTest;

class DependsExternal extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DependsExternal(AnotherTest::class, 'testMethod')]
    public function test(): void
    {
    }
}

?>
