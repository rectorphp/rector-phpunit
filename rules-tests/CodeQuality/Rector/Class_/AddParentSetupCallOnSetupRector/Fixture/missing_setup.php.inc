<?php

namespace Utils\Rector\Tests\Rector\AddParentSetupCallOnSetupRector\Fixture;

use PHPUnit\Framework\TestCase;

class MissingSetup extends TestCase
{
    protected function setUp(): void
    {
    }
}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddParentSetupCallOnSetupRector\Fixture;

use PHPUnit\Framework\TestCase;

class MissingSetup extends TestCase
{
    protected function setUp(): void
    {
        parent::setUp();
    }
}

?>
