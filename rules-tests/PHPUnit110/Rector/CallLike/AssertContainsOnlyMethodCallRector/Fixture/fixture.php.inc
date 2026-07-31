<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertContainsOnly('array', [[]]);
        $this->assertContainsOnly('bool', [true]);
        $this->assertContainsOnly('boolean', [true]);
        $this->assertContainsOnly('callable', [fn () => 0]);
        $this->assertContainsOnly('double', [1.0]);
        $this->assertContainsOnly('float', [1.0]);
        $this->assertContainsOnly('int', [1]);
        $this->assertContainsOnly('integer', [1]);
        $this->assertContainsOnly('iterable', [[]]);
        $this->assertContainsOnly('null', [null]);
        $this->assertContainsOnly('numeric', [12]);
        $this->assertContainsOnly('object', [new \stdClass()]);
        $this->assertContainsOnly('real', [1.0]);
        $this->assertContainsOnly('resource', [$resource]);
        $this->assertContainsOnly('resource (closed)', [$closedResource]);
        $this->assertContainsOnly('scalar', ['']);
        $this->assertContainsOnly('string', ['']);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertContainsOnlyArray([[]]);
        $this->assertContainsOnlyBool([true]);
        $this->assertContainsOnlyBool([true]);
        $this->assertContainsOnlyCallable([fn () => 0]);
        $this->assertContainsOnlyFloat([1.0]);
        $this->assertContainsOnlyFloat([1.0]);
        $this->assertContainsOnlyInt([1]);
        $this->assertContainsOnlyInt([1]);
        $this->assertContainsOnlyIterable([[]]);
        $this->assertContainsOnlyNull([null]);
        $this->assertContainsOnlyNumeric([12]);
        $this->assertContainsOnlyObject([new \stdClass()]);
        $this->assertContainsOnlyFloat([1.0]);
        $this->assertContainsOnlyResource([$resource]);
        $this->assertContainsOnlyClosedResource([$closedResource]);
        $this->assertContainsOnlyScalar(['']);
        $this->assertContainsOnlyString(['']);
    }
}

?>
