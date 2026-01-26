<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Symfony\Component\HttpFoundation\Request;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $args = [
            $this->createMock(Request::class),
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Symfony\Component\HttpFoundation\Request;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $args = [
            new \Symfony\Component\HttpFoundation\Request(),
        ];
    }
}

?>
