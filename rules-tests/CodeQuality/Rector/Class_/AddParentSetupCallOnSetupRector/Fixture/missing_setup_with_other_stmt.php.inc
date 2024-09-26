<?php

namespace Utils\Rector\Tests\Rector\AddParentSetupCallOnSetupRector\Fixture;

use PHPUnit\Framework\TestCase;

class MissingSetUpWithOtherStmt extends TestCase {
    protected function setUp(): void
    {
        echo 'init';
    }
}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddParentSetupCallOnSetupRector\Fixture;

use PHPUnit\Framework\TestCase;

class MissingSetUpWithOtherStmt extends TestCase {
    protected function setUp(): void
    {
        parent::setUp();
        echo 'init';
    }
}

?>