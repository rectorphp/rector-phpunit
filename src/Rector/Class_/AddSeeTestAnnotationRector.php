<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Stmt\Class_;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\Reflection\ReflectionProvider;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\Naming\TestClassNameResolver;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\AddSeeTestAnnotationRector\AddSeeTestAnnotationRectorTest
 */
final class AddSeeTestAnnotationRector extends AbstractRector
{
    /**
     * @var string
     */
    private const SEE = 'see';

    public function __construct(
        private ReflectionProvider $reflectionProvider,
        private PhpDocTagRemover $phpDocTagRemover,
        private TestClassNameResolver $testClassNameResolver
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add @see annotation test of the class for faster jump to test. Make it FQN, so it stays in the annotation, not in the PHP source code.',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
class SomeService
{
}

use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
/**
 * @see \SomeServiceTest
 */
class SomeService
{
}

use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        $className = $this->getName($node);
        if ($className === null) {
            return null;
        }

        $possibleTestClassNames = $this->testClassNameResolver->resolve($className);
        $matchingTestClassName = $this->matchExistingClassName($possibleTestClassNames);

        if ($this->shouldSkipClass($node)) {
            return null;
        }

        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($node);

        $this->removeNonExistingClassSeeAnnotation($phpDocInfo);

        if ($matchingTestClassName === null) {
            return null;
        }

        if ($this->hasAlreadySeeAnnotation($phpDocInfo, $matchingTestClassName)) {
            return null;
        }

        $newSeeTagNode = $this->createSeePhpDocTagNode($matchingTestClassName);
        $phpDocInfo->addPhpDocTagNode($newSeeTagNode);

        return $node;
    }

    private function shouldSkipClass(Class_ $class): bool
    {
        // we are in the test case
        if ($this->isName($class, '*Test')) {
            return true;
        }

        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($class);

        /** @var PhpDocTagNode[] $seePhpDocTagNodes */
        $seePhpDocTagNodes = $phpDocInfo->getTagsByName(self::SEE);

        // is the @see annotation already added
        foreach ($seePhpDocTagNodes as $seePhpDocTagNode) {
            if (! $seePhpDocTagNode->value instanceof GenericTagValueNode) {
                continue;
            }

            /** @var GenericTagValueNode $genericTagValueNode */
            $genericTagValueNode = $seePhpDocTagNode->value;

            $seeTagClass = ltrim($genericTagValueNode->value, '\\');

            if ($this->reflectionProvider->hasClass($seeTagClass)) {
                return true;
            }
        }

        return false;
    }

    private function createSeePhpDocTagNode(string $className): PhpDocTagNode
    {
        return new PhpDocTagNode('@see', new GenericTagValueNode('\\' . $className));
    }

    private function hasAlreadySeeAnnotation(PhpDocInfo $phpDocInfo, string $testCaseClassName): bool
    {
        /** @var PhpDocTagNode[] $seePhpDocTagNodes */
        $seePhpDocTagNodes = $phpDocInfo->getTagsByName(self::SEE);

        foreach ($seePhpDocTagNodes as $seePhpDocTagNode) {
            if (! $seePhpDocTagNode->value instanceof GenericTagValueNode) {
                continue;
            }

            $possibleClassName = $seePhpDocTagNode->value->value;

            // annotation already exists
            if ($possibleClassName === '\\' . $testCaseClassName) {
                return true;
            }
        }

        return false;
    }

    private function removeNonExistingClassSeeAnnotation(PhpDocInfo $phpDocInfo): void
    {
        $seePhpDocTagNodes = $phpDocInfo->getTagsByName(self::SEE);

        /** @var PhpDocTagNode[] $seePhpDocTagNodes */
        foreach ($seePhpDocTagNodes as $seePhpDocTagNode) {
            if (! $seePhpDocTagNode->value instanceof GenericTagValueNode) {
                continue;
            }

            $possibleClassName = $seePhpDocTagNode->value->value;
            if (! $this->isSeeTestCaseClass($possibleClassName)) {
                continue;
            }

            if ($this->reflectionProvider->hasClass($possibleClassName)) {
                continue;
            }

            // remove old annotation
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $seePhpDocTagNode);
        }
    }

    private function isSeeTestCaseClass(string $possibleClassName): bool
    {
        if (! \str_starts_with($possibleClassName, '\\')) {
            return false;
        }

        return \str_ends_with($possibleClassName, 'Test');
    }

    /**
     * @param string[] $classNames
     */
    private function matchExistingClassName(array $classNames): ?string
    {
        foreach ($classNames as $possibleTestClassName) {
            if (! $this->reflectionProvider->hasClass($possibleTestClassName)) {
                continue;
            }

            return $possibleTestClassName;
        }

        return null;
    }
}
