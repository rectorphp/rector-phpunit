<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @requires PHPUnit >= 10
 * @requires PHPUnit 5
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
#[\PHPUnit\Framework\Attributes\RequiresPhpunit('>= 5')]
final class RequiresPHPUnit extends TestCase
{
}

?>
