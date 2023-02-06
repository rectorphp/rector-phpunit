<?php

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class ExtendsTest extends TestCase
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class ExtendsTestCase extends TestCase
{
}

?>
