<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNotMatchPositionNamedArgument extends TestCase
{
    public function testSomething()
    {
        self::assertJsonResponse(contentType: 'text/html');
    }

    protected static function assertJsonResponse(int $statusCode = 200, string $contentType = 'application/json'): void
    {
		// logic
    }
}