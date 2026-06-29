<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\MockObjectVarToStubRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipNonStubNativeTypeTest extends TestCase
{
    /**
     * @var FieldModel|MockObject
     */
    private \PHPUnit\Framework\MockObject\MockObject $leadFieldModel;
}
