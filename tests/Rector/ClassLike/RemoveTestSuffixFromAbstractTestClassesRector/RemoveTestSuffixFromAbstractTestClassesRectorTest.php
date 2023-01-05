<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector;

use Iterator;
use Nette\Utils\FileSystem;
use Rector\FileSystemRector\ValueObject\AddedFileWithContent;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;
use Webmozart\Assert\Assert;

final class RemoveTestSuffixFromAbstractTestClassesRectorTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);

        Assert::string($this->originalTempFilePath);
        $originalDirectory = dirname($this->originalTempFilePath);

        $expectedAddedFileWithContent = new AddedFileWithContent(
            $originalDirectory . '/ReplaceAbstractClassWithSuffixTestCase.php',
            FileSystem::read(__DIR__ . '/Fixture/replace_abstract_class_with_suffix_test.php.inc')
        );
        $this->assertFileWasAdded($expectedAddedFileWithContent);

//        $expectedAddedFileWithContent = new AddedFileWithContent(
//            $originalDirectory . '/SkipAbstractClassWithoutSuffix.php',
//            FileSystem::read(__DIR__ . '/Fixture/skip_abstract_class_without_suffix.php.inc')
//        );
//        $this->assertFileWasAdded($expectedAddedFileWithContent);
    }

    public function provideData(): Iterator
    {
        return $this->yieldFilesFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured_rule.php';
    }
}
