<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Symfony\Component\HttpFoundation\Request;

final class HandleStaticCall extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(
            $this->createMock(Request::class),
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Symfony\Component\HttpFoundation\Request;

final class HandleStaticCall extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(
            new \Symfony\Component\HttpFoundation\Request(),
        );
    }
}

?>
