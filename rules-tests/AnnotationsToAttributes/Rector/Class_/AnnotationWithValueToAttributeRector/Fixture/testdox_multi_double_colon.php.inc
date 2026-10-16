<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestdoxMultiDoubleColon extends TestCase
{
    /**
     * @testdox ::property is true ::property2 is true as well
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

final class TestdoxMultiDoubleColon extends TestCase
{
    #[\PHPUnit\Framework\Attributes\TestDox('::property is true ::property2 is true as well')]
    public function myAwesomeTest(): void
    {
    }
}

?>
