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
use Rector\ValueObject\MethodName;
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
        if ($this->shouldSkipClass($node)) {
            return null;
        }

        $mockObjectPropertyNames = $this->matchMockObjectPropertyNames($node);

        // there are no mock object properties
        if ($mockObjectPropertyNames === []) {
            return null;
        }

        // @todo add the attribute if has more than 1 public test* method
        $testMethodCount = 0;

        foreach ($node->getMethods() as $classMethod) {
            if ($this->testsNodeAnalyzer->isTestClassMethod($classMethod)) {
                // is a mock property used in the method?
                // skip if so

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

    /**
     * @return string[]
     */
    private function matchMockObjectPropertyNames(Class_ $class): array
    {
        $propertyNames = [];

        foreach ($class->getProperties() as $property) {
            if (! $property->type instanceof Name) {
                continue;
            }

            if (! $this->isName($property->type, PHPUnitClassName::MOCK_OBJECT)) {
                continue;
            }

            $propertyNames[] = $this->getName($property->props[0]);
        }

        return $propertyNames;
    }

    private function shouldSkipClass(Class_ $class): bool
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($class)) {
            return true;
        }

        // attribute must exist for the rule to work
        if (! $this->reflectionProvider->hasClass(PHPUnitAttribute::ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS)) {
            return true;
        }

        // already filled
        if ($this->attributeFinder->hasAttributeByClasses(
            $class,
            [PHPUnitAttribute::ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS]
        )) {
            return true;
        }

        // has mock objects properties and setUp() method?

        $setupClassMethod = $class->getMethod(MethodName::SET_UP);
        return ! $setupClassMethod instanceof ClassMethod;
    }
}
