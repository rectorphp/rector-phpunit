<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsForDataProviderRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class SkipDynamicMethodCall extends TestCase
{
    #[DataProvider('methodNameProvider')]
    public function testUnusableMethods(string $method): void
    {
        $sut = new \stdClass();

        $this->expectException(\RuntimeException::class);

        $sut->$method();
    }

    public static function methodNameProvider(): iterable
    {
        yield ['realMethodName'];
    }
}
