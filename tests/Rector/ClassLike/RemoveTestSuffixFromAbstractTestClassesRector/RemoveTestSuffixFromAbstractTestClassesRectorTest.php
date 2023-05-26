<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector;

use Nette\Utils\FileSystem;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class RemoveTestSuffixFromAbstractTestClassesRectorTest extends AbstractRectorTestCase
{
    public function testNoChanges(): void
    {
        $this->doTestFile(__DIR__ . '/Fixture/skip_abstract_class_without_suffix.php.inc');
    }

    public function testChanges(): void
    {
        $this->doTestFile(__DIR__ . '/Fixture/extends_test.php.inc');

        $this->assertFileWasAdded(
            __DIR__ . '/Fixture/ExtendsTestCase.php',
            FileSystem::read(__DIR__ . '/Expected/ExtendsTestCase.php')
        );

        $this->doTestFile(__DIR__ . '/Fixture/no_namespace_extends_test.php.inc');

        $this->assertFileWasAdded(
            __DIR__ . '/Fixture/NoNamespaceExtendsTestCase.php',
            FileSystem::read(__DIR__ . '/Expected/NoNamespaceExtendsTestCase.php')
        );

        $this->doTestFile(__DIR__ . '/Fixture/follow_up_parent_class_name_change.php.inc');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured_rule.php';
    }
}
