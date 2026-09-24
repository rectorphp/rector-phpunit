<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipNewWithVariableArg extends \PHPUnit\Framework\TestCase
{
    public function test($result, $amount, $className, array $args)
    {
        $this->assertEquals($result, new Money($amount));
        $this->assertEquals($result, new $className(100));
        $this->assertEquals($result, new Money(...$args));
        $this->assertEquals($result, new Money(amount: 100));
        $this->assertEquals($result, new class(100) {
            public function __construct(public int $amount)
            {
            }
        });
    }
}

?>
