<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source;

use Stringable;

final class SimpleStringable implements Stringable
{
    public function __toString()
    {
        return 'value';
    }
}
