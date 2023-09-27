<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoversFunction extends TestCase
{
    /**
     * @covers ::someFunction()
     */
    public function testOne()
    {
    }

    /**
     * @covers ::someFunction()
     */
    public function testTwo()
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
    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}

?>
