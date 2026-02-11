<?php

namespace Rector\PHPUnit\Tests\PHPUnit80\Rector\MethodCall\SpecificAssertContainsRector\Fixture;

class SkipOnPossibleArrayTest extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $this->assertContains("DummyNumber", $this->getBody());
    }

    public function getBody(): array|string
    {
        if (rand(0, 1)) {
            return "DummyNumber";
        }

        return ["DummyNumber"];
    }
}