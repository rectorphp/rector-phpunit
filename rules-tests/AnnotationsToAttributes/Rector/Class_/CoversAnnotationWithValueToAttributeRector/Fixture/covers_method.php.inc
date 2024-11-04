<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoversMethod extends TestCase
{
    /**
     * @covers \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass::foo
     */
    public function test()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversMethod(\Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source\ExistingClass::class, 'foo')]
final class CoversMethod extends TestCase
{
    public function test()
    {
    }
}

?>
