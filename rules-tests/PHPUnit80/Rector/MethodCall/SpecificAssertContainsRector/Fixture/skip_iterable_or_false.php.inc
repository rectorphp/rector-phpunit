<?php

namespace Rector\PHPUnit\Tests\PHPUnit80\Rector\MethodCall\SpecificAssertContainsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IterableOrFalse extends TestCase
{
    public function test()
    {
        $this->assertContains('foo', $this->getIterableOrFalse());
    }

    /**
     * @return []|false
     */
    public function getIterableOrFalse()
    {
        if (mt_rand(0, 1)) {
            return [];
        }

        return false;
    }
}

?>
