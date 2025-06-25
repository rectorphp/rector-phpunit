<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\StringCastAssertStringContainsStringRector\Fixture;

use PHPUnit\Framework\TestCase;

class SomeTest extends TestCase
{
    public function testSomething(?string $value)
    {
        $this->assertStringContainsString('foo', $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\StringCastAssertStringContainsStringRector\Fixture;

use PHPUnit\Framework\TestCase;

class SomeTest extends TestCase
{
    public function testSomething(?string $value)
    {
        $this->assertStringContainsString('foo', (string) $value);
    }
}

?>
