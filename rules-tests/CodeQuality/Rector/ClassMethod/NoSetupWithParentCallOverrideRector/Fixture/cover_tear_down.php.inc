<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoverTearDown extends TestCase
{
    #[\Override]
    protected function tearDown(): void
    {
        parent::tearDown();

        $some = 'value';
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CoverTearDown extends TestCase
{
    protected function tearDown(): void
    {
        parent::tearDown();
        $some = 'value';
    }
}

?>
