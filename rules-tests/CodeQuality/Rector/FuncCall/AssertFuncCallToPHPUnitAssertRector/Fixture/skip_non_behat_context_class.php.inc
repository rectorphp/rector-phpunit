<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

final class SchemaValidationContext
{
    public function some($response)
    {
        assert($response instanceof \DateTime, 'only remaining option');
    }
}
