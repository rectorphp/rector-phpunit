<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDifferentObject extends TestCase
{
    public function testMe()
    {
        $this->transport('webhook')
            ->dispatched()
            ->assertCount(1)
            ->assertContains(SendWebhookMessage::class);
    }
}
