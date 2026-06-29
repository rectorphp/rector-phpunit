<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

final class SkipNonTestClass
{
    /**
     * @var FormBuilderInterface
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}
