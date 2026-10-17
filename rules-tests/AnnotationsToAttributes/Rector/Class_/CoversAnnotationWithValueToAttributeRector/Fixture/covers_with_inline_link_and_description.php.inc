<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @copyright Example {@link https://example.com}. Additional description.
 * @todo Do this.{@link https://example.com}.
 * @covers \Tests\BarController
 */
class CoversWithInlineLinkAndDescription extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @copyright Example {@link https://example.com}. Additional description.
 * @todo Do this.{@link https://example.com}.
 */
#[\PHPUnit\Framework\Attributes\CoversClass(\Tests\BarController::class)]
class CoversWithInlineLinkAndDescription extends TestCase
{
}

?>
