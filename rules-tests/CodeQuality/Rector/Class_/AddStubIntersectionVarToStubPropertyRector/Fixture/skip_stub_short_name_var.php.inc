<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\Stub;
use PHPUnit\Framework\TestCase;

final class SkipStubShortNameVarTest extends TestCase
{
    /**
     * @var Stub
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}
