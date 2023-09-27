<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @covers ::someFunction()
 */
final class CoversFunction extends TestCase
{
    public function testOne(): void
    {
    }

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
final class CoversFunction extends TestCase
{
    public function testOne(): void
    {
    }

    public function testTwo(): void
    {
    }
}

?>
