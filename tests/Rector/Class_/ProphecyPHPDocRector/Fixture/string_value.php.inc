<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\ProphecyPHPDocRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ClassConstTest extends TestCase
{
    private $prophecy;

    protected function setUp(): void
    {
        $this->prophecy = $this->prophesize('App\SomeClass');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\ProphecyPHPDocRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ClassConstTest extends TestCase
{
    /**
     * @var \Prophecy\Prophecy\ObjectProphecy<\App\SomeClass>
     */
    private $prophecy;

    protected function setUp(): void
    {
        $this->prophecy = $this->prophesize('App\SomeClass');
    }
}

?>
