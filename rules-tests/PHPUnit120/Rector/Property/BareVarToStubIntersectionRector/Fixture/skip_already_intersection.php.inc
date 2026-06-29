<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAlreadyIntersectionTest extends TestCase
{
    /**
     * @var FormBuilderInterface&Stub
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}
