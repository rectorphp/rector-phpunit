<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class SimpleContext
{
    public function some($response)
    {
        assert($response instanceof \DateTime);

        assert($response instanceof \DateTimeInterface, 'extra message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class SimpleContext
{
    public function some($response)
    {
        \PHPUnit\Framework\Assert::assertInstanceOf(\DateTime::class, $response);

        \PHPUnit\Framework\Assert::assertInstanceOf(\DateTimeInterface::class, $response, 'extra message');
    }
}

?>
