<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoversFunction extends TestCase
{
    /**
     * @covers ::someFunction()
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

final class CoversFunction extends TestCase
{
    #[\PHPUnit\Framework\Attributes\CoversFunction('someFunction')]
    public function test()
    {
    }
}

?>
