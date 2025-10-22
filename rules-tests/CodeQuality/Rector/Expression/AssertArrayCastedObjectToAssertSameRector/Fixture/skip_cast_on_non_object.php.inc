<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Source\SomeObjectWithPublicProperties;

final class SkipCastOnNonObject extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someObject = 'some string';

        $this->assertSame([
            'name' => 'John',
            'surname' => 'Doe',
        ], (array) $someObject);
    }
}
