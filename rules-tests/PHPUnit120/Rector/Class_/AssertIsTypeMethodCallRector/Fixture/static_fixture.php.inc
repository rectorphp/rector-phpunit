<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class StaticFixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertThat([], self::isType('array'));
        $this->assertThat(true, self::isType('bool'));
        $this->assertThat(true, self::isType('boolean'));
        $this->assertThat(fn () => 0, self::isType('callable'));
        $this->assertThat(1.0, self::isType('float'));
        $this->assertThat(1.0, self::isType('double'));
        $this->assertThat(1, self::isType('int'));
        $this->assertThat(1, self::isType('integer'));
        $this->assertThat([], self::isType('iterable'));
        $this->assertThat(null, self::isType('null'));
        $this->assertThat(12, self::isType('numeric'));
        $this->assertThat(new \stdClass(), self::isType('object'));
        $this->assertThat(1.0, self::isType('real'));
        $this->assertThat($resource, self::isType('resource'));
        $this->assertThat($closedResource, self::isType('resource (closed)'));
        $this->assertThat('', self::isType('scalar'));
        $this->assertThat('', self::isType('string'));
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class StaticFixture extends TestCase
{
    public function testMethod(): void
    {
        $this->assertThat([], self::isArray());
        $this->assertThat(true, self::isBool());
        $this->assertThat(true, self::isBool());
        $this->assertThat(fn () => 0, self::isCallable());
        $this->assertThat(1.0, self::isFloat());
        $this->assertThat(1.0, self::isFloat());
        $this->assertThat(1, self::isInt());
        $this->assertThat(1, self::isInt());
        $this->assertThat([], self::isIterable());
        $this->assertThat(null, self::isNull());
        $this->assertThat(12, self::isNumeric());
        $this->assertThat(new \stdClass(), self::isObject());
        $this->assertThat(1.0, self::isFloat());
        $this->assertThat($resource, self::isResource());
        $this->assertThat($closedResource, self::isClosedResource());
        $this->assertThat('', self::isScalar());
        $this->assertThat('', self::isString());
    }
}
?>
