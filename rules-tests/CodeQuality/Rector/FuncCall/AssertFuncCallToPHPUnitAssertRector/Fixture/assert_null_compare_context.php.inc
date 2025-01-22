<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class AssertNullCompareContext
{
    public function some($response)
    {
        assert($response !== null);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class AssertNullCompareContext
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertNotNull($response);
    }
}

?>
