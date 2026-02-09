<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddKeysExistsAssertForKeyUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipEmptyDim extends TestCase
{
    public function test(): void
    {
        $data = $this->getData();
        $this->assertSame(123, $data[]);
    }

    private function getData(): array
    {
        if (mt_rand(0, 1)) {
            return ['key' => 123];
        }

        return [];
    }
}
