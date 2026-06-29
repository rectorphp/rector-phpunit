<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\MockObjectVarToStubRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoMockObjectTest extends TestCase
{
    /**
     * @var FieldModel
     */
    private \PHPUnit\Framework\MockObject\Stub $leadFieldModel;
}
