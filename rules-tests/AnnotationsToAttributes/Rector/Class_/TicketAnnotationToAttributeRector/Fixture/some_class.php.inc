<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\TicketAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @ticket 123
 */
final class SomeTest extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\TicketAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\Ticket('123')]
final class SomeTest extends TestCase
{
}

?>
