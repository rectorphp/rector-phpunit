<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture;

/**
 * @doto àreprendre et refactorer
 */
class SurroundedDoc
{
}

class SurroundedDocTest extends \PHPUnit\Framework\TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture;

/**
 * @doto àreprendre et refactorer
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture\SurroundedDocTest
 */
class SurroundedDoc
{
}

class SurroundedDocTest extends \PHPUnit\Framework\TestCase
{
}

?>
