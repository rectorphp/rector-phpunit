<?php

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class Factory
{
    public function create(): \stdClass
    {
        return new \stdClass();
    }
}

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

final class DemoTest extends WebTestCase
{
    public function testCreate(): void
    {
        $this->expectNotToPerformAssertions();
        
        $factory = new Factory();

        $factory->create();
    }
}

?>
-----
<?php

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

final class DemoTest extends WebTestCase
{
    /**
     * @doesNotPerformAssertions
     */
    public function testCreate(): void
    {
        $factory = new Factory();

        $factory->create();
    }
}

?>
