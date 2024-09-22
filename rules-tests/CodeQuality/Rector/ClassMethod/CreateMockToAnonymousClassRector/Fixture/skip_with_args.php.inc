<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Source\ToBeFixturedClass;

final class SkipWithArgs extends TestCase
{
    public function createFromUrl($url)
    {
        $requestMock = $this->createMock(ToBeFixturedClass::class);

        $requestMock
            ->method('getPathInfo')
            ->willReturn($url);

        return $requestMock;
    }
}
