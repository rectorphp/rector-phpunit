<?php

namespace Utils\Rector\Tests\Rector\AddParentSetupCallOnSetupRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\CoversClass;

class SkipSetUpExists extends TestCase {
    protected function setUp(): void
    {
        parent::setUp();
    }
}

?>
