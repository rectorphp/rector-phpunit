<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\ExceptionAnnotationRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class ExceptionAnnotationRectorTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    public function provideData(): Iterator
    {
        return $this->yieldFilePathsFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured_rule.php';
    }
}
