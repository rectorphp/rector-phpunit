<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @copyright Some Value. Something.({@link https://example.com}).
 * @covers \Tests\BarController
 */
class CoversWithInlineLinkAndPunctuation extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @copyright Some Value. Something.({@link https://example.com}).
 */
#[\PHPUnit\Framework\Attributes\CoversClass(\Tests\BarController::class)]
class CoversWithInlineLinkAndPunctuation extends TestCase
{
}

?>
