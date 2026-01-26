<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    #[\Override]
    protected function setUp(): void
    {
        parent::setUp();

        $some = 'value';
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    protected function setUp(): void
    {
        parent::setUp();
        $some = 'value';
    }
}

?>
