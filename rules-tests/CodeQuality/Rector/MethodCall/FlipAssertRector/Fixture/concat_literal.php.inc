<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ConcatLiteral extends \PHPUnit\Framework\TestCase
{
    private const PREFIX = 'item';

    public function test($result)
    {
        $this->assertSame($result->getName(), 'foo' . 'bar');
        $this->assertSame($result->getPath(), __DIR__ . '/fixture.json');
        $this->assertSame($result->getId(), self::PREFIX . '-1');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ConcatLiteral extends \PHPUnit\Framework\TestCase
{
    private const PREFIX = 'item';

    public function test($result)
    {
        $this->assertSame('foo' . 'bar', $result->getName());
        $this->assertSame(__DIR__ . '/fixture.json', $result->getPath());
        $this->assertSame(self::PREFIX . '-1', $result->getId());
    }
}

?>
