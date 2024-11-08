<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Source;

use ArrayAccess;

class WithMagicGet implements ArrayAccess {
    public $container = [
        "one"   => 1,
        "two"   => 2,
        "three" => 3,
    ];

    public function offsetSet($offset, $value): void {
        if (is_null($offset)) {
            $this->container[] = $value;
        } else {
            $this->container[$offset] = $value;
        }
    }

    public function offsetExists($offset): bool {
        return isset($this->container[$offset]);
    }

    public function offsetUnset($offset): void {
        unset($this->container[$offset]);
    }

    public function offsetGet($offset): mixed {
        return isset($this->container[$offset]) ? $this->container[$offset] : null;
    }

    public function __get(string $name): mixed
    {
        return $this->offsetGet($name);
    }
}