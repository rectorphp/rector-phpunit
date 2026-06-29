<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\MockObjectVarToStubRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class UnionTypeTest extends TestCase
{
    /**
     * @var FieldModel|MockObject
     */
    private \PHPUnit\Framework\MockObject\Stub $leadFieldModel;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Property\MockObjectVarToStubRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class UnionTypeTest extends TestCase
{
    /**
     * @var FieldModel|\PHPUnit\Framework\MockObject\Stub
     */
    private \PHPUnit\Framework\MockObject\Stub $leadFieldModel;
}

?>
