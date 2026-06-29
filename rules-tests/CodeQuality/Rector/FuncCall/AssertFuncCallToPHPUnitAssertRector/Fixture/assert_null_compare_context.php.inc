<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use Behat\Behat\Context\Context;

final class AssertNullCompareContext implements Context
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

use Behat\Behat\Context\Context;

final class AssertNullCompareContext implements Context
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertNotNull($response);
    }
}

?>
