<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Fixture;

use CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Source\SomeService;
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    private static $someService;

    public static function setUpBeforeClass(): void
    {
        self::$someService = new SomeService();
    }

    public function test()
    {
        $result = self::$someService->getValue();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Fixture;

use CodeQuality\Rector\Class_\SetUpBeforeClassToSetUpRector\Source\SomeService;
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    private $someService;

    protected function setUp(): void
    {
        $this->someService = new SomeService();
    }

    public function test()
    {
        $result = $this->someService->getValue();
    }
}

?>
