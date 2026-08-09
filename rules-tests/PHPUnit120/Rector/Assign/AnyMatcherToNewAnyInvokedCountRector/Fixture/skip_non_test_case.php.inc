<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Assign\AnyMatcherToNewAnyInvokedCountRector\Fixture;

final class SkipNonTestCase
{
    public function run(): void
    {
        $matcher = $this->any();
    }

    public function any(): string
    {
        return 'any';
    }
}
