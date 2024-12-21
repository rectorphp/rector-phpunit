<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DynamicBool extends TestCase
{
    public function testIsHeaderLine(string $line, bool $expected): void
    {
        $this->assertEquals($expected, $this->returnsBool($line));
    }

    public function returnsBool(): bool {
        return rand(0,1) ? true : false;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DynamicBool extends TestCase
{
    public function testIsHeaderLine(string $line, bool $expected): void
    {
        $this->assertSame($expected, $this->returnsBool($line));
    }

    public function returnsBool(): bool {
        return rand(0,1) ? true : false;
    }
}

?>
