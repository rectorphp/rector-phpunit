<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AbstractTestCaseWithItem extends TestCase
{
    protected $item;

    protected function setUpItem($item): void
    {
        $this->item = $item;
    }
}
