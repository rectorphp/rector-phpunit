<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @covers \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass
 */
final class CoversClass extends TestCase
{
    public function test()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass::class)]
final class CoversClass extends TestCase
{
    public function test()
    {
    }
}

?>
