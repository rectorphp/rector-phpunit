<?php

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

abstract class MyTestCase extends WebTestCase 
{
    abstract public function testSomeThing(): void;
}

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

final class DemoTest extends MyTestCase
{
    public function testSomeThing(): void
    {
        $this->assertTrue(true);
    }
}

?>
