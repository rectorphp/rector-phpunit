<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

class RequiresSetting extends TestCase
{
    /**
     * @requires setting date.timezone Europe/Berlin
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

class RequiresSetting extends TestCase
{
    #[\PHPUnit\Framework\Attributes\RequiresSetting('date.timezone', 'Europe/Berlin')]
    public function testWithRequires()
    {
    }
}

?>
