<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\Class_\TestListenerToHooksRector;

use Iterator;
use PHPUnit\Framework\Attributes\DataProvider;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class TestListenerToHooksRectorTest extends AbstractRectorTestCase
{
    #[DataProvider('provideData')]
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    public static function provideData(): Iterator
    {
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured_rule.php';
    }

    /**
     * The rule is bound to a PHPUnit version older than the one installed here
     */
    protected function provideComposerJsonFilePath(): string
    {
        return __DIR__ . '/config/composer.json';
    }
}
