<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class InnerClassTest extends AbstractRectorTestCase
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
        return $this->yieldFilePathsFromDirectory(__DIR__ . '/FixtureInnerClass');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/inner_class_configured_rule.php';
    }
}
