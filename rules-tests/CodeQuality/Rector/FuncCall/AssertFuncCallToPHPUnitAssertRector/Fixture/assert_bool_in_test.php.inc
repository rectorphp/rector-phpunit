<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertBoolInTest extends TestCase
{
    public function some($response)
    {
        assert((bool) $response);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertBoolInTest extends TestCase
{
    public function some($response)
    {
        $this->assertTrue((bool) $response);
    }
}

?>
