<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Core\Rector\AbstractRector;
use Rector\Core\ValueObject\PhpVersionFeature;
use Rector\NodeTypeResolver\Node\AttributeKey;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\DataProviderAnnotationToAttributeRectorTest
 */
final class DataProviderAnnotationToAttributeRector extends AbstractRector implements MinPhpVersionInterface
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly PhpAttributeGroupFactory $phpAttributeGroupFactory,
        private readonly PhpDocTagRemover $phpDocTagRemover
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Change dataProvider annotations to attribute', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider someMethod()
     */
    public function test(): void
    {
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('test')]
    public function test(): void
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
        return [ClassMethod::class];
    }

    public function provideMinPhpVersion(): int
    {
        return PhpVersionFeature::ATTRIBUTES;
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);
        if (! $phpDocInfo instanceof PhpDocInfo) {
            return null;
        }

        /** @var PhpDocTagNode[] $desiredTagValueNodes */
        $desiredTagValueNodes = $phpDocInfo->getTagsByName('dataProvider');
        if ($desiredTagValueNodes === []) {
            return null;
        }

        $currentClass = $node->getAttribute(AttributeKey::PARENT_NODE);
        if (! $currentClass instanceof Class_) {
            return null;
        }

        foreach ($desiredTagValueNodes as $desiredTagValueNode) {
            if (! $desiredTagValueNode->value instanceof GenericTagValueNode) {
                continue;
            }

            $originalAttributeValue = $desiredTagValueNode->value->value;

            $node->attrGroups[] = $this->createAttributeGroup($originalAttributeValue);

            // cleanup
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $desiredTagValueNode);
        }

        if (! $phpDocInfo->hasChanged()) {
            return null;
        }

        return $node;
    }

    private function createAttributeGroup(string $originalAttributeValue): AttributeGroup
    {
        $methodName = trim($originalAttributeValue, '()');

        $className = '';
        if (str_contains($methodName, '::')) {
            [$className, $methodName] = explode('::', $methodName, 2);
        }

        if ($className !== '') {
            if ($className[0] !== '\\') {
                $className = '\\' . $className;
            }

            return $this->phpAttributeGroupFactory->createFromClassWithItems(
                'PHPUnit\Framework\Attributes\DataProviderExternal',
                [$className . '::class', $methodName]
            );
        }

        return $this->phpAttributeGroupFactory->createFromClassWithItems(
            'PHPUnit\Framework\Attributes\DataProvider',
            [$methodName]
        );
    }
}
