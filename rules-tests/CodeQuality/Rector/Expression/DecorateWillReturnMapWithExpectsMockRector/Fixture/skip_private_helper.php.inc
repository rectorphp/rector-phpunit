<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SkipPrivateHelper extends \PHPUnit\Framework\TestCase
{
    private function createSomeMock()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturnMap([1, 2]);

        return $someMock;
    }
}
