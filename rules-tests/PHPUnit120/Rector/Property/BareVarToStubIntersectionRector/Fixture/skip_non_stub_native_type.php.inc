<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonStubNativeTypeTest extends TestCase
{
    /**
     * @var FormBuilderInterface
     */
    private \PHPUnit\Framework\MockObject\MockObject $formBuilder;
}
