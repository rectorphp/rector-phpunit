<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

/**
 * @backupGlobals enabled
 * @backupGlobals ENABLED
 * @backupGlobals disabled
 * @backupGlobals DISABLED
 */
final class SomeTest extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\BackupGlobals(true)]
#[\PHPUnit\Framework\Attributes\BackupGlobals(true)]
#[\PHPUnit\Framework\Attributes\BackupGlobals(false)]
#[\PHPUnit\Framework\Attributes\BackupGlobals(false)]
final class SomeTest extends TestCase
{
}

?>
