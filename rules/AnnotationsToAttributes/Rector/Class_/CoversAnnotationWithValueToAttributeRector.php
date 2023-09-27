<?php

declare(strict_types=1);

namespace Rector\PHPUnit\AnnotationsToAttributes\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Comments\NodeDocBlock\DocBlockUpdater;
use Rector\Core\Rector\AbstractRector;
use Rector\Core\ValueObject\PhpVersionFeature;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\CoversAnnotationWithValueToAttributeRectorTest
 */
final class CoversAnnotationWithValueToAttributeRector extends AbstractRector implements MinPhpVersionInterface
{
    public function __construct(
        private readonly PhpDocTagRemover $phpDocTagRemover,
        private readonly PhpAttributeGroupFactory $phpAttributeGroupFactory,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly DocBlockUpdater $docBlockUpdater,
        private readonly PhpDocInfoFactory $phpDocInfoFactory
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Change covers annotations with value to attribute', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

/**
 * @covers SomeClass
 */
final class SomeTest extends TestCase
{
    /**
     * @covers ::someFunction
     */
    public function test()
    {
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\CoversFunction;

#[CoversClass(SomeClass::class)]
final class SomeTest extends TestCase
{
    #[CoversFunction('someFunction')]
    public function test()
    {
    }
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
        return [Class_::class, ClassMethod::class];
    }

    public function provideMinPhpVersion(): int
    {
        return PhpVersionFeature::ATTRIBUTES;
    }

    /**
     * @param Class_|ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        if (!$this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }
        if ($node instanceof Class_) {
            $coversAttributeGroups = $this->resolveClassAttributes($node);
            if ($coversAttributeGroups === []) {
                return null;
            }
            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);
            $node->attrGroups = array_merge($node->attrGroups, $coversAttributeGroups);
        }
        if ($node instanceof ClassMethod) {
            $this->removeMethodCoversAnnotations($node);
            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);
        }

        return $node;
    }

    private function createAttributeGroup(string $annotationValue): AttributeGroup
    {
        if (str_starts_with($annotationValue, '::')) {
            $attributeClass = 'PHPUnit\Framework\Attributes\CoversFunction';
            $attributeValue = trim($annotationValue, ':()');
        } else {
            $attributeClass = 'PHPUnit\Framework\Attributes\CoversClass';
            $attributeValue = trim($annotationValue) . '::class';
        }

        return $this->phpAttributeGroupFactory->createFromClassWithItems($attributeClass, [$attributeValue]);
    }

    /**
     * @return array<string, AttributeGroup>
     */
    private function resolveClassAttributes(Class_ $node): array
    {
        $coversDefaultGroups = [];
        $coversGroups        = [];
        $methodGroups        = [];
        $hasCoversDefault    = false;
        $phpDocInfo          = $this->phpDocInfoFactory->createFromNode($node);
        if ($phpDocInfo instanceof PhpDocInfo) {
            $coversDefaultGroups = $this->handleCoversDefaultClass($phpDocInfo);
            $hasCoversDefault    = count($coversDefaultGroups) > 0;
            $coversGroups        = $this->handleCovers($phpDocInfo, $hasCoversDefault);
        }

        foreach ($node->getMethods() as $methodNode) {
            $methodGroups = array_merge($methodGroups, $this->resolveMethodAttributes($methodNode, $hasCoversDefault));
        }

        return array_merge($coversDefaultGroups, $coversGroups, $methodGroups);
    }

    /**
     * @return AttributeGroup[]
     */
    private function handleCoversDefaultClass(PhpDocInfo $phpDocInfo): array
    {
        $attributeGroups      = [];
        $desiredTagValueNodes = $phpDocInfo->getTagsByName('coversDefaultClass');
        foreach ($desiredTagValueNodes as $desiredTagValueNode) {
            if (!$desiredTagValueNode->value instanceof GenericTagValueNode) {
                continue;
            }
            $attributeGroups[] = $this->createAttributeGroup($desiredTagValueNode->value->value);
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $desiredTagValueNode);
        }

        return $attributeGroups;
    }

    private function handleCovers(PhpDocInfo $phpDocInfo, bool $hasCoversDefault): array
    {
        $attributeGroups      = [];
        $desiredTagValueNodes = $phpDocInfo->getTagsByName('covers');
        foreach ($desiredTagValueNodes as $desiredTagValueNode) {
            if (!$desiredTagValueNode->value instanceof GenericTagValueNode) {
                continue;
            }
            $covers = $desiredTagValueNode->value->value;
            if (str_starts_with($covers, '\\')) {
                $attributeGroups[$covers] = $this->createAttributeGroup($covers);
            } elseif (!$hasCoversDefault && str_starts_with($covers, '::')) {
                $attributeGroups[$covers] = $this->createAttributeGroup($covers);
            }
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $desiredTagValueNode);
        }

        return $attributeGroups;
    }

    /**
     * @return array<string, AttributeGroup>
     */
    private function resolveMethodAttributes(ClassMethod $node, bool $hasCoversDefault): array
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);
        if (!$phpDocInfo instanceof PhpDocInfo) {
            return [];
        }
        $attributeGroups      = [];
        $desiredTagValueNodes = $phpDocInfo->getTagsByName('covers');
        foreach ($desiredTagValueNodes as $desiredTagValueNode) {
            if (!$desiredTagValueNode->value instanceof GenericTagValueNode) {
                continue;
            }
            $covers = $desiredTagValueNode->value->value;
            if (str_starts_with($covers, '\\')) {
                $covers                   = $this->getClass($covers);
                $attributeGroups[$covers] = $this->createAttributeGroup($covers);
            } elseif (!$hasCoversDefault && str_starts_with($covers, '::')) {
                $attributeGroups[$covers] = $this->createAttributeGroup($covers);
            }

            $attributeGroups[$covers] = $this->createAttributeGroup($covers);
        }

        return $attributeGroups;
    }

    private function removeMethodCoversAnnotations(ClassMethod $node): void
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);
        if (!$phpDocInfo instanceof PhpDocInfo) {
            return;
        }
        $desiredTagValueNodes = $phpDocInfo->getTagsByName('covers');
        foreach ($desiredTagValueNodes as $desiredTagValueNode) {
            if (!$desiredTagValueNode->value instanceof GenericTagValueNode) {
                continue;
            }
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $desiredTagValueNode);
        }
    }

    private function getClass(string $classWithMethod): string
    {
        return (string)preg_replace('/::.*$/', '', $classWithMethod);
    }
}
