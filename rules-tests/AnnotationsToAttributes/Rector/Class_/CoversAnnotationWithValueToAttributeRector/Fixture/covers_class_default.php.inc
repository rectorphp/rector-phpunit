<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @coversDefaultClass \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass
 * @covers ::__construct
 */
final class CoversClassDefault extends TestCase
{
    /**
     * @covers ::foo
     * @covers \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\HelperClass
     */
    public function testFoo()
    {
    }

    /**
     * @covers ::bar
     * @covers \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\HelperClass
     */
    public function testBar()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass::class)]
#[\PHPUnit\Framework\Attributes\CoversClass(\Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\HelperClass::class)]
final class CoversClassDefault extends TestCase
{
    public function testFoo()
    {
    }

    public function testBar()
    {
    }
}

?>
