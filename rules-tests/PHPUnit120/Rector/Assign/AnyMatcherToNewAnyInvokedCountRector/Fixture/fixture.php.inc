<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Assign\AnyMatcherToNewAnyInvokedCountRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function test(): void
    {
        $matcher = $this->any();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Assign\AnyMatcherToNewAnyInvokedCountRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function test(): void
    {
        $matcher = new \PHPUnit\Framework\MockObject\Rule\AnyInvokedCount();
    }
}

?>
