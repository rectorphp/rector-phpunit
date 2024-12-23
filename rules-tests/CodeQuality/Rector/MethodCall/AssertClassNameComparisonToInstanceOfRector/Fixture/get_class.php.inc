<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertClassNameComparisonToInstanceOfRector\Fixture;

use stdClass;

final class GetClass extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $something = new stdClass();
        self::assertSame('stdClass', get_class($something));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertClassNameComparisonToInstanceOfRector\Fixture;

use stdClass;

final class GetClass extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $something = new stdClass();
        self::assertInstanceOf('stdClass', $something);
    }
}

?>