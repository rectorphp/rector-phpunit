<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\ClassLike;

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassLike;
use Rector\Core\Application\FileSystem\RemovedAndAddedFilesCollector;
use Rector\Core\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see Rector\PHPUnit\Tests\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector\RemoveTestSuffixFromAbstractTestClassesRectorTest
 */
final class RemoveTestSuffixFromAbstractTestClassesRector extends AbstractRector
{
    public function __construct(
        private readonly RemovedAndAddedFilesCollector $removedAndAddedFilesCollector,
    )
    {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Rename Suffix for abstract test class as it may not end with directory suffix (default is Test)', [
            new CodeSample(
                <<<'CODE_SAMPLE'
// app/ReplaceAbstractClassWithSuffixTest.php
abstract class ReplaceAbstractClassWithSuffixTest
{
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
// app/ReplaceAbstractClassWithSuffixTestCase.php
abstract class ReplaceAbstractClassWithSuffixTestCase
{
}
CODE_SAMPLE
            ),
        ]);
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [ClassLike::class];
    }

    /**
     * @param ClassLike $node
     */
    public function refactor(Node $node): ?Node
    {
        if (!$node->isAbstract()) {
            return null;
        }
        $directorySuffix = $this->getPhpUnitDirectorySuffix();

        $filePath = $this->file->getFilePath();
        $basename = pathinfo($filePath, PATHINFO_FILENAME);

        if (!str_ends_with($basename, $directorySuffix)) {
            return null;
        }

        $className = $this->getName($node);
        if ($className === null) {
            return null;
        }

        $classShortName = $this->nodeNameResolver->getShortName($className);
        // no match → rename file
        $newFileLocation = dirname($filePath) . DIRECTORY_SEPARATOR . $classShortName . 'Case.php';
        $this->removedAndAddedFilesCollector->addMovedFile($this->file, $newFileLocation);


        return null;
    }

    private function getPhpUnitDirectorySuffix(): string
    {
        // TODO check in phpunit config if this is different.
        return 'Test';
    }
}
