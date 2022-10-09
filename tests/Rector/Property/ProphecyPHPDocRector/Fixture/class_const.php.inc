<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use App\SomeClass;
use PHPUnit\Framework\TestCase;

final class ClassConstTest extends TestCase
{
    private $prophecy;

    public function setUp(): void
    {
        $this->prophecy = $this->prophesize(SomeClass::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use App\SomeClass;
use PHPUnit\Framework\TestCase;

final class ClassConstTest extends TestCase
{
    /**
     * @var \Prophecy\Prophecy\ObjectProphecy<\App\SomeClass>
     */
    private $prophecy;

    public function setUp(): void
    {
        $this->prophecy = $this->prophesize(SomeClass::class);
    }
}

?>
