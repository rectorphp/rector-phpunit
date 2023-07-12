<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture;

/**
 * @see \SomeRandom\MissingTest
 */
final class RemoveNonExistingSee
{
}

class RemoveNonExistingSeeTest
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture\RemoveNonExistingSeeTest
 */
final class RemoveNonExistingSee
{
}

class RemoveNonExistingSeeTest
{
}

?>
