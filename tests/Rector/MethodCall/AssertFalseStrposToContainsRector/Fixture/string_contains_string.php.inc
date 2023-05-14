<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

final class StringContainsString extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $body = 'Content-Length:';
        $this->assertNotFalse(strpos($body, 'Content'));
        $this->assertNotFalse(strpos($body, 'Length'));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

final class StringContainsString extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $body = 'Content-Length:';
        $this->assertStringContainsString('Content', $body);
        $this->assertStringContainsString('Length', $body);
    }
}

?>
