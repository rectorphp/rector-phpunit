<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit120\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Attribute;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Name;
use PhpParser\Node\Name\FullyQualified;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Reflection\ReflectionProvider;
use Rector\Doctrine\NodeAnalyzer\AttributeFinder;
use Rector\PHPUnit\Enum\PHPUnitAttribute;
use Rector\PHPUnit\Enum\PHPUnitClassName;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\AllowMockObjectsWithoutExpectationsAttributeRectorTest
 *
 * @see https://github.com/sebastianbergmann/phpunit/commit/24c208d6a340c3071f28a9b5cce02b9377adfd43
 */
final class AllowMockObjectsWithoutExpectationsAttributeRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly AttributeFinder $attributeFinder,
        private readonly ReflectionProvider $reflectionProvider
    ) {
    }

    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Class_
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        // attribute must exist for the rule to work
        if (! $this->reflectionProvider->hasClass(PHPUnitAttribute::ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS)) {
            return null;
        }

        // already filled
        if ($this->attributeFinder->hasAttributeByClasses(
            $node,
            [PHPUnitAttribute::ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS]
        )) {
            return null;
        }

        // has mock objects properties and setUp() method?

        if (! $node->getMethod('setUp') instanceof ClassMethod) {
            return null;
        }

        if (! $this->hasMockObjectProperty($node)) {
            return null;
        }

        // @todo add the attribute if has more than 1 public test* method
        $testMethodCount = 0;

        foreach ($node->getMethods() as $classMethod) {
            if ($this->testsNodeAnalyzer->isTestClassMethod($classMethod)) {
                ++$testMethodCount;
            }
        }

        if ($testMethodCount < 2) {
            return null;
        }

        // add attribute
        $node->attrGroups[] = new AttributeGroup([
            new Attribute(new FullyQualified(PHPUnitAttribute::ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS)),
        ]);

        return $node;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add #[AllowMockObjectsWithoutExpectations] attribute to PHPUnit test classes with mock properties used in multiple methods',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;
final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createMock(SomeService::class);
    }

    public function testOne(): void
    {
        // use $this->someServiceMock
    }

    public function testTwo(): void
    {
        // use $this->someServiceMock
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations;

#[AllowMockObjectsWithoutExpectations]
final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createMock(SomeService::class);
    }

    public function testOne(): void
    {
        // use $this->someServiceMock
    }

    public function testTwo(): void
    {
        // use $this->someServiceMock
    }
}
CODE_SAMPLE
                ),

            ]
        );

    }

    private function hasMockObjectProperty(Class_ $class): bool
    {
        foreach ($class->getProperties() as $property) {
            if (! $property->type instanceof Name) {
                continue;
            }

            if ($this->isName($property->type, PHPUnitClassName::MOCK_OBJECT)) {
                return true;
            }
        }

        return false;
    }
}
