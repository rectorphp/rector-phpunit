<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\MockObjectVarToStubRector\Fixture;

final class SkipNonTestClass
{
    /**
     * @var FieldModel|MockObject
     */
    private \PHPUnit\Framework\MockObject\Stub $leadFieldModel;
}
