<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SkipProtectedNonTestMethod extends \PHPUnit\Framework\TestCase
{
    protected function prepareSomeMock()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturnMap([1, 2]);
    }
}
