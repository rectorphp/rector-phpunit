<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PHPStan\Type\Constant\ConstantArrayType;
use PHPStan\Type\FloatType;
use PHPStan\Type\IntegerType;
use PHPStan\Type\StringType;
use PHPStan\Type\Type;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\IdentifierManipulator;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\AssertEqualsToSameRectorTest
 */
final class AssertEqualsToSameRector extends AbstractRector
{
    /**
     * @var array<string, string>
     */
    private const RENAME_METHODS_MAP = [
        'assertEquals' => 'assertSame',
        'assertNotEquals' => 'assertNotSame',
    ];

    /**
     * We exclude
     * - bool because this is taken care of AssertEqualsParameterToSpecificMethodsTypeRector
     * - null because this is taken care of AssertEqualsParameterToSpecificMethodsTypeRector
     *
     * @var array<class-string<Type>>
     */
    private const SCALAR_TYPES = [FloatType::class, IntegerType::class, StringType::class, ConstantArrayType::class];

    public function __construct(
        private readonly IdentifierManipulator $identifierManipulator,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns `assertEquals()` into stricter `assertSame()` for scalar values in PHPUnit TestCase',
            [new CodeSample('$this->assertEquals(2, $result);', '$this->assertSame(2, $result);')]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [MethodCall::class, StaticCall::class];
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $methodNames = array_keys(self::RENAME_METHODS_MAP);
        if (! $this->isNames($node->name, $methodNames)) {
            return null;
        }

        $args = $node->getArgs();
        if (! isset($args[0])) {
            return null;
        }

        $valueNodeType = $this->nodeTypeResolver->getType($args[0]->value);
        if (! $this->isScalarType($valueNodeType)) {
            return null;
        }

        $hasChanged = $this->identifierManipulator->renameNodeWithMap($node, self::RENAME_METHODS_MAP);
        return $hasChanged ? $node : null;
    }

    private function isScalarType(Type $valueNodeType): bool
    {
        foreach (self::SCALAR_TYPES as $scalarType) {
            if (is_a($valueNodeType, $scalarType, true)) {
                return true;
            }
        }

        return false;
    }
}
