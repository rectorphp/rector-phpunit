<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\SpecificAssertContainsWithoutIdentityRector\Fixture;

use PHPUnit\Framework\TestCase;
use stdClass;

final class SkipNoSecondArg extends TestCase
{
    public function test()
    {
        $objects = [ new stdClass(), new stdClass(), new stdClass() ];
        $this->transport()->queue()->assertContains(new stdClass());
    }
}