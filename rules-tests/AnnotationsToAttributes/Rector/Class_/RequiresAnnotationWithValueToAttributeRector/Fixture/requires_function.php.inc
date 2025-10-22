<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RequiresFunction extends TestCase
{
    /**
     * @requires function someFunction
     * @requires function \some\className::someMethod
     */
    public function testWithRequires()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RequiresFunction extends TestCase
{
    #[\PHPUnit\Framework\Attributes\RequiresFunction('someFunction')]
    #[\PHPUnit\Framework\Attributes\RequiresMethod(\some\className::class, 'someMethod')]
    public function testWithRequires()
    {
    }
}

?>
