<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UsesInTest extends TestCase
{
    /**
     * @uses Foo::Bar
     */
    public function run()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\UsesClass(Foo::Bar)]
final class UsesInTest extends TestCase
{
    public function run()
    {
    }
}

?>
