<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertThat([], $this->isType('array'));
        $this->assertThat(true, $this->isType('bool'));
        $this->assertThat(true, $this->isType('boolean'));
        $this->assertThat(fn () => 0, $this->isType('callable'));
        $this->assertThat(1.0, $this->isType('float'));
        $this->assertThat(1.0, $this->isType('double'));
        $this->assertThat(1, $this->isType('int'));
        $this->assertThat(1, $this->isType('integer'));
        $this->assertThat([], $this->isType('iterable'));
        $this->assertThat(null, $this->isType('null'));
        $this->assertThat(12, $this->isType('numeric'));
        $this->assertThat(new \stdClass(), $this->isType('object'));
        $this->assertThat(1.0, $this->isType('real'));
        $this->assertThat($resource, $this->isType('resource'));
        $this->assertThat($closedResource, $this->isType('resource (closed)'));
        $this->assertThat('', $this->isType('scalar'));
        $this->assertThat('', $this->isType('string'));
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertThat([], $this->isArray());
        $this->assertThat(true, $this->isBool());
        $this->assertThat(true, $this->isBool());
        $this->assertThat(fn () => 0, $this->isCallable());
        $this->assertThat(1.0, $this->isFloat());
        $this->assertThat(1.0, $this->isFloat());
        $this->assertThat(1, $this->isInt());
        $this->assertThat(1, $this->isInt());
        $this->assertThat([], $this->isIterable());
        $this->assertThat(null, $this->isNull());
        $this->assertThat(12, $this->isNumeric());
        $this->assertThat(new \stdClass(), $this->isObject());
        $this->assertThat(1.0, $this->isFloat());
        $this->assertThat($resource, $this->isResource());
        $this->assertThat($closedResource, $this->isClosedResource());
        $this->assertThat('', $this->isScalar());
        $this->assertThat('', $this->isString());
    }
}
?>
