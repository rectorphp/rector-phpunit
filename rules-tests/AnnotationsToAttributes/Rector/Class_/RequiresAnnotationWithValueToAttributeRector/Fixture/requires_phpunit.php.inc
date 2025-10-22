<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @requires PHPUnit >= 10
 */
final class RequiresPHPUnit extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\RequiresPhpunit('>= 10')]
final class RequiresPHPUnit extends TestCase
{
}

?>
