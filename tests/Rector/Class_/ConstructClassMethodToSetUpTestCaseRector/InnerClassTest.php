<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;
use Symplify\SmartFileSystem\SmartFileInfo;

final class InnerClassTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    /**
     * @return Iterator<SmartFileInfo>
     */
    public function provideData(): Iterator
    {
        return $this->yieldFilesFromDirectory(__DIR__ . '/FixtureInnerClass');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/inner_class_configured_rule.php';
    }
}
