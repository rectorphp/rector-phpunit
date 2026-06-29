<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use Behat\Behat\Context\Context;

final class AssertCompareContext implements Context
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

use Behat\Behat\Context\Context;

final class AssertCompareContext implements Context
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertEquals(2.5, $response);
        \PHPUnit\Framework\Assert::assertSame('yes', $response);
    }
}

?>
