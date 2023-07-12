<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

final class MyContainsStrposTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertNotFalse(strpos($node, 'foo'));
        $this->assertFalse(stripos($node, 'foo'), 'message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

final class MyContainsStrposTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertStringContainsString('foo', $node);
        $this->assertStringNotContainsString('foo', $node, 'message');
    }
}

?>
