<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class KeepIfNoParentCall extends TestCase
{
    #[\Override]
    protected function setUp(): void
    {
        $some = 'value';
    }
}
