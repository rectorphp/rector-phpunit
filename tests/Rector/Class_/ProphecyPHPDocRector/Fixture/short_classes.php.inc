<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use PHPUnit\Framework\TestCase;

final class ShortClassesTest extends TestCase
{
    private $prophecy;

    private $prophecy2;

    public function setUp(): void
    {
        $this->prophecy = $this->prophesize(\ReflectionClass::class);
        $this->prophecy2 = $this->prophesize(\stdClass::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Property\ProphecyPHPDocRectorTest\Fixture;

use PHPUnit\Framework\TestCase;

final class ShortClassesTest extends TestCase
{
    /**
     * @var \Prophecy\Prophecy\ObjectProphecy<\ReflectionClass>
     */
    private $prophecy;

    /**
     * @var \Prophecy\Prophecy\ObjectProphecy<\stdClass>
     */
    private $prophecy2;

    public function setUp(): void
    {
        $this->prophecy = $this->prophesize(\ReflectionClass::class);
        $this->prophecy2 = $this->prophesize(\stdClass::class);
    }
}

?>
