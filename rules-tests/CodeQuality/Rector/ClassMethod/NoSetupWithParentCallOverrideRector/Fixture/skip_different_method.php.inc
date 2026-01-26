<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDifferentMethod extends TestCase
{
    #[\Override]
    protected function testThat(): void
    {
        parent::testThat();

        $some = 'value';
    }
}
