<?php

namespace Rector\PHPUnit\Tests\PHPUnit70\Rector\ClassMethod\ScenarioToTestAnnotationRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeScenarioTest extends TestCase
{
    /**
     * @scenario
     */
    public function someMethod()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit70\Rector\ClassMethod\ScenarioToTestAnnotationRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeScenarioTest extends TestCase
{
    /**
     * @test
     */
    public function someMethod()
    {
    }
}

?>
