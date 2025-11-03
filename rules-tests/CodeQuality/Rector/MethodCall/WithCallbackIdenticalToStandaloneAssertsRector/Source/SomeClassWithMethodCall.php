<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Source;

final class SomeClassWithMethodCall
{
    public function isReady(): bool
    {
        return mt_rand(0, 1) === 1;
    }
}
