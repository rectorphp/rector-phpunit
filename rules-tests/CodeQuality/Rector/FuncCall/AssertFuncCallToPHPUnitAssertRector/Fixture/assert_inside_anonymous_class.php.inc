<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertInsideAnonymousClass extends TestCase
{
    public function some($response)
    {
        return new class($response) {
            public function __construct($response)
            {
                assert((bool) $response);
            }
        };
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertInsideAnonymousClass extends TestCase
{
    public function some($response)
    {
        return new class($response) {
            public function __construct($response)
            {
                \PHPUnit\Framework\Assert::assertTrue((bool) $response);
            }
        };
    }
}

?>
