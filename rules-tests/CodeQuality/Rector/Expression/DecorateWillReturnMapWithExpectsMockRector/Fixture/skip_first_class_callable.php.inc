<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SkipFirstClassCallable extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturnMap(...);
    }
}

?>