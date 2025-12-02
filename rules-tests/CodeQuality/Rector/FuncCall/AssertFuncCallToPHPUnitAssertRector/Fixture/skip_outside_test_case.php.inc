<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class SkipOutsideTestCase
{
    public function some($response)
    {
        assert((bool) $response);
    }
}
