<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class AssertCompareContext
{
    public function some($response)
    {
        assert($response == 2.5);
        assert($response === 'yes');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class AssertCompareContext
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertEquals(2.5, $response);
        \PHPUnit\Framework\Assert::assertSame('yes', $response);
    }
}

?>
