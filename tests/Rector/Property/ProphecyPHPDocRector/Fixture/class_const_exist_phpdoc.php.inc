<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use App\SomeClass;
use PHPUnit\Framework\TestCase;
use Prophecy\Prophecy\ObjectProphecy;

final class ClassConstExistPHPDOCTest extends TestCase
{
    /**
     * @var ObjectProphecy
     */
    private $someObjectProphecy;

    public function setUp(): void
    {
        $prophecy = $this->prophesize(SomeClass::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use App\SomeClass;
use PHPUnit\Framework\TestCase;
use Prophecy\Prophecy\ObjectProphecy;

final class ClassConstExistPHPDOCTest extends TestCase
{
    /**
     * @var ObjectProphecy<SomeClass>
     */
    private $someObjectProphecy;

    public function setUp(): void
    {
        $prophecy = $this->prophesize(SomeClass::class);
    }
}

?>
