<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAssertObjectHasAttribute extends TestCase
{
    public function test(object $someObject)
    {
        // has a direct replacement in assertObjectHasProperty(), renamed by the composer-based set
        $this->assertObjectHasAttribute('property', $someObject);
        $this->assertObjectNotHasAttribute('property', $someObject);
    }
}

?>
