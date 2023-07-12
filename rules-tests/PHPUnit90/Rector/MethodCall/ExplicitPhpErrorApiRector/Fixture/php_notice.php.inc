<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ExplicitPhpErrorApiRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RefactorNotice extends TestCase
{
    public function test()
    {
        $this->expectException(\PHPUnit\Framework\TestCase\Notice::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ExplicitPhpErrorApiRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RefactorNotice extends TestCase
{
    public function test()
    {
        $this->expectNotice();
    }
}

?>
