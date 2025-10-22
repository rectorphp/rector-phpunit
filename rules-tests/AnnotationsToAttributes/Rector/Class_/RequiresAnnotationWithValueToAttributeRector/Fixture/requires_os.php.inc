<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @requires OS Windows
 * @requires OSFAMILY Darwin
 */
class RequiresOS extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\RequiresOperatingSystem('Windows')]
#[\PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily('Darwin')]
class RequiresOS extends TestCase
{
}

?>
