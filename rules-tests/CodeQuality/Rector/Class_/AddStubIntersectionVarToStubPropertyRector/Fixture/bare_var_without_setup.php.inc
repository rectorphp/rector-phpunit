<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class BareVarWithoutSetupTest extends TestCase
{
    /**
     * @var FormBuilderInterface
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class BareVarWithoutSetupTest extends TestCase
{
    /**
     * @var \PHPUnit\Framework\MockObject\Stub&FormBuilderInterface
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}

?>
