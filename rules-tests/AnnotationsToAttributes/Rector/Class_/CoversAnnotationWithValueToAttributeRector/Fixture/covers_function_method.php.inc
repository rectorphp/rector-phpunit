<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoversFunctionMethod extends TestCase
{
    /**
     * @covers ::someFunction()
     */
    public function testOne(): void
    {
    }

    /**
     * @covers ::someFunction()
     */
    public function testTwo(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversFunction('someFunction')]
final class CoversFunctionMethod extends TestCase
{
    public function testOne(): void
    {
    }

    public function testTwo(): void
    {
    }
}

?>
