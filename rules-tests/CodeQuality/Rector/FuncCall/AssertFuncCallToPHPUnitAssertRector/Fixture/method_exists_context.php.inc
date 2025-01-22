<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class MethodExistsContext
{
    public function some($response)
    {
        assert(method_exists($response, 'some_method'));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class MethodExistsContext
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertTrue(method_exists($response, 'some_method'));
    }
}

?>
