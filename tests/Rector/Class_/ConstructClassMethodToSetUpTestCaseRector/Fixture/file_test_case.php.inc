<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FileTestCase extends TestCase
{
    public function __construct($name = null)
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FileTestCase extends TestCase
{
    protected function setUp()
    {
    }
}

?>
