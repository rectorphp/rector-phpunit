<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class StaticDataProviderClassMethodRectorTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    /**
     * @return Iterator<string>
     */
    public function provideData(): Iterator
    {
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured_rule.php';
    }
}
