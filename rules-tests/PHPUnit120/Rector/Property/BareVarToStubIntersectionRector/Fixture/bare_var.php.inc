<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class BareVarTest extends TestCase
{
    /**
     * @var FormBuilderInterface
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class BareVarTest extends TestCase
{
    /**
     * @var FormBuilderInterface&Stub
     */
    private \PHPUnit\Framework\MockObject\Stub $formBuilder;
}

?>
