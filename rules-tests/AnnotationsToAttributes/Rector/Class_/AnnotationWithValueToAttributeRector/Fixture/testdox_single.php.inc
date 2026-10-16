<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestdoxSingle extends TestCase
{
    /**
     * @testdox ::property is true
     */
    public function myAwesomeTest(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestdoxSingle extends TestCase
{
    #[\PHPUnit\Framework\Attributes\TestDox('::property is true')]
    public function myAwesomeTest(): void
    {
    }
}

?>
