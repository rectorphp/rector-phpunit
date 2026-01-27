<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector\Source\SomeFunctionalTestCase;

final class SkipIndirectParentTestCase extends SomeFunctionalTestCase
{
    #[\Override]
    protected function setUp(): void
    {
        parent::setUp();

        $some = 'value';
    }
}
