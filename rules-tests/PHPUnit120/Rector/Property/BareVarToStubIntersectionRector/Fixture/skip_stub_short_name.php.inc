<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

use PHPUnit\Framework\MockObject\Stub;
use PHPUnit\Framework\TestCase;

final class SkipStubShortNameTest extends TestCase
{
    /**
     * @var Stub
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}
