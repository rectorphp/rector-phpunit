<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @backupGlobals enabled
 */
final class SomeTest extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\BackupGlobals(true)]
final class SomeTest extends TestCase
{
}

?>
