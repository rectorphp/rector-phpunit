<?php

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture\ExtendsTest;

final class FollowUpParentClassNameChange extends ExtendsTest
{
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture\ExtendsTest;

final class FollowUpParentClassNameChange extends \Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\Fixture\ExtendsTestCase
{
}

?>
