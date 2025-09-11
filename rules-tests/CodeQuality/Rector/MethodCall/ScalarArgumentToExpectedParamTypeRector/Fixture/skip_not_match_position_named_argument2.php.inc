<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoTmatchPositionNamedArgument2 extends TestCase
{
    public function testResizeHeight(): void
    {
        $this->createImage(width: 20, height: 40);
    }

    public function createImage(
        string $content = 'content',
        int $width = 30,
        int $height = 50,
        int $resolution = 96
    ): void {

    }
}