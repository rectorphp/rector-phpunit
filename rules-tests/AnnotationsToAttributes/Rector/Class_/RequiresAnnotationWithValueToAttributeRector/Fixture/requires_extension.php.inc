<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @requires extension mysqli
 * @requires extension mysqli >= 8.3.0
 */
final class BarController extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\RequiresAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli')]
#[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli', '>= 8.3.0')]
final class BarController extends TestCase
{
}

?>
