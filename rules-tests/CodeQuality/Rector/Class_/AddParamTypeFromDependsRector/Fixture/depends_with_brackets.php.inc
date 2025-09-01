<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddParamTypeFromDependsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DependsWithBrackets extends TestCase
{
    public function test(): \stdClass
    {
        return new \stdClass();
    }

    /**
     * @depends test()
     */
    public function testWithDepends($value)
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddParamTypeFromDependsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DependsWithBrackets extends TestCase
{
    public function test(): \stdClass
    {
        return new \stdClass();
    }

    /**
     * @depends test()
     */
    public function testWithDepends(\stdClass $value)
    {
    }
}

?>
