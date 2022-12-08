<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Core\Contract\Rector\ConfigurableRectorInterface;
use Rector\Core\Rector\AbstractRector;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;
use Rector\PHPUnit\ValueObject\AnnotationWithValueToAttribute;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use Webmozart\Assert\Assert;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\AnnotationWithValueToAttributeRector\AnnotationWithValueToAttributeRectorTest
 */
final class AnnotationWithValueToAttributeRector extends AbstractRector implements ConfigurableRectorInterface
{
    /**
     * @var AnnotationWithValueToAttribute[]
     */
    private array $annotationWithValueToAttributes = [];

    public function __construct(
        private readonly PhpDocTagRemover $phpDocTagRemover,
        private readonly PhpAttributeGroupFactory $phpAttributeGroupFactory,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Change annotations with value to attribute', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

/**
 * @backupGlobals enabled
 */
final class SomeTest extends TestCase
{
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\BackupGlobals;

#[BackupGlobals(true)]
final class SomeTest extends TestCase
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
        return [Class_::class, ClassMethod::class];
    }

    /**
     * @param Class_|ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);
        if (! $phpDocInfo instanceof PhpDocInfo) {
            return null;
        }

        $hasChanged = false;

        foreach ($this->annotationWithValueToAttributes as $annotationWithValueToAttribute) {
            /** @var PhpDocTagNode[] $desiredTagValueNodes */
            $desiredTagValueNodes = $phpDocInfo->getTagsByName($annotationWithValueToAttribute->getAnnotationName());

            foreach ($desiredTagValueNodes as $desiredTagValueNode) {
                if ($desiredTagValueNode->value instanceof GenericTagValueNode) {
                    $attributeValue = $this->resolveAttributeValue(
                        $desiredTagValueNode->value,
                        $annotationWithValueToAttribute
                    );

                    $hasChanged = true;

                    $attributeGroup = $this->phpAttributeGroupFactory->createFromClassWithItems(
                        $annotationWithValueToAttribute->getAttributeClass(),
                        [$attributeValue]
                    );

                    $node->attrGroups[] = $attributeGroup;

                    // cleanup
                    $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $desiredTagValueNode);
                }
            }
        }

        if ($hasChanged) {
            return $node;
        }

        return null;
    }

    /**
     * @param mixed[] $configuration
     */
    public function configure(array $configuration): void
    {
        Assert::allIsInstanceOf($configuration, AnnotationWithValueToAttribute::class);

        $this->annotationWithValueToAttributes = $configuration;
    }

    private function resolveAttributeValue(
        GenericTagValueNode $genericTagValueNode,
        AnnotationWithValueToAttribute $annotationWithValueToAttribute
    ): mixed {
        $valueMap = $annotationWithValueToAttribute->getValueMap();
        if ($valueMap === []) {
            // no map? convert value as it is
            return $genericTagValueNode->value;
        }

        $originalValue = strtolower($genericTagValueNode->value);
        return $valueMap[$originalValue];
    }
}
