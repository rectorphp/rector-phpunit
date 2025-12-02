<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertInsideStaticClosure extends TestCase
{
    public function some($response)
    {
        static function () use ($response) {
            assert((bool) $response);
        };
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertInsideStaticClosure extends TestCase
{
    public function some($response)
    {
        static function () use ($response) {
            \PHPUnit\Framework\Assert::assertTrue((bool) $response);
        };
    }
}

?>
