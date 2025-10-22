<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @requires PHP 8.0
 */
class RequiresPHP extends TestCase
{
    /**
     * @requires PHP > 8.4
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

#[\PHPUnit\Framework\Attributes\RequiresPhp('>= 8.0')]
class RequiresPHP extends TestCase
{
    #[\PHPUnit\Framework\Attributes\RequiresPhp('> 8.4')]
    public function testWithRequires()
    {
    }
}

?>
