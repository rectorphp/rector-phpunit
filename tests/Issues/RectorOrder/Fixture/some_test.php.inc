<?php

namespace Rector\PHPUnit\Tests\Issues\RectorOrder\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $this->assertTrue(strpos('foo', 'f') !== false);
        $this->assertNotSame(false, strpos('foo', 'f'));

        $this->assertTrue(strpos($headers['Authorization'][0], 'oauth_body_hash') !== false);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Issues\RectorOrder\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $this->assertStringContainsString('f', 'foo');
        $this->assertStringContainsString('f', 'foo');

        $this->assertStringContainsString('oauth_body_hash', $headers['Authorization'][0]);
    }
}

?>
