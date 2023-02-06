<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Stmt\Class_;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Core\Rector\AbstractRector;
use Rector\Core\ValueObject\PhpVersionFeature;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\CoversAnnotationWithValueToAttributeRector\CoversAnnotationWithValueToAttributeRectorTest
 */
final class CoversAnnotationWithValueToAttributeRector extends AbstractRector implements MinPhpVersionInterface
{
    public function __construct(
        private readonly PhpDocTagRemover $phpDocTagRemover,
        private readonly PhpAttributeGroupFactory $phpAttributeGroupFactory,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
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
        return [Class_::class];
    }

    public function provideMinPhpVersion(): int
    {
        return PhpVersionFeature::ATTRIBUTES;
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        // resolve covers class first
        $classPhpDocInfo = $this->phpDocInfoFactory->createFromNode($node);

        $attributeGroups = [];

        if ($classPhpDocInfo instanceof PhpDocInfo) {
            /** @var PhpDocTagNode[] $desiredTagValueNodes */
            $desiredTagValueNodes = $classPhpDocInfo->getTagsByName('covers');

            foreach ($desiredTagValueNodes as $desiredTagValueNode) {
                if (! $desiredTagValueNode->value instanceof GenericTagValueNode) {
                    continue;
                }

                $attributeGroups[] = $this->createAttributeGroup($desiredTagValueNode->value->value);

                // cleanup
                $this->phpDocTagRemover->removeTagValueFromNode($classPhpDocInfo, $desiredTagValueNode);
            }
        }

        // resolve covers function
        foreach ($node->getMethods() as $classMethod) {
            $classMethodPhpDocInfo = $this->phpDocInfoFactory->createFromNode($classMethod);
            if (! $classMethodPhpDocInfo instanceof PhpDocInfo) {
                continue;
            }

            /** @var PhpDocTagNode[] $desiredTagValueNodes */
            $desiredTagValueNodes = $classMethodPhpDocInfo->getTagsByName('covers');

            foreach ($desiredTagValueNodes as $desiredTagValueNode) {
                if (! $desiredTagValueNode->value instanceof GenericTagValueNode) {
                    continue;
                }

                $attributeGroups[] = $this->createAttributeGroup($desiredTagValueNode->value->value);

                // cleanup
                $this->phpDocTagRemover->removeTagValueFromNode($classMethodPhpDocInfo, $desiredTagValueNode);
            }
        }

        if ($attributeGroups === []) {
            return null;
        }

        $node->attrGroups = array_merge($node->attrGroups, $attributeGroups);

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
}
