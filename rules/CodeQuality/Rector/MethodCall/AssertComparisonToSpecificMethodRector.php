<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\BinaryOp;
use PhpParser\Node\Expr\BinaryOp\Equal;
use PhpParser\Node\Expr\BinaryOp\Greater;
use PhpParser\Node\Expr\BinaryOp\GreaterOrEqual;
use PhpParser\Node\Expr\BinaryOp\Identical;
use PhpParser\Node\Expr\BinaryOp\NotEqual;
use PhpParser\Node\Expr\BinaryOp\NotIdentical;
use PhpParser\Node\Expr\BinaryOp\Smaller;
use PhpParser\Node\Expr\BinaryOp\SmallerOrEqual;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PHPStan\Type\Constant\ConstantArrayType;
use PHPStan\Type\ConstantScalarType;
use Rector\PHPUnit\NodeAnalyzer\IdentifierManipulator;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\ValueObject\BinaryOpWithAssertMethod;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\AssertComparisonToSpecificMethodRectorTest
 */
final class AssertComparisonToSpecificMethodRector extends AbstractRector
{
    /**
     * @var BinaryOpWithAssertMethod[]
     */
    private array $binaryOpWithAssertMethods = [];

    public function __construct(
        private readonly IdentifierManipulator $identifierManipulator,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
        $this->binaryOpWithAssertMethods = [
            new BinaryOpWithAssertMethod(Identical::class, 'assertSame', 'assertNotSame'),
            new BinaryOpWithAssertMethod(NotIdentical::class, 'assertNotSame', 'assertSame'),
            new BinaryOpWithAssertMethod(Equal::class, 'assertEquals', 'assertNotEquals'),
            new BinaryOpWithAssertMethod(NotEqual::class, 'assertNotEquals', 'assertEquals'),
            new BinaryOpWithAssertMethod(Greater::class, 'assertLessThan', 'assertGreaterThan'),
            new BinaryOpWithAssertMethod(Smaller::class, 'assertGreaterThan', 'assertLessThan'),
            new BinaryOpWithAssertMethod(
                GreaterOrEqual::class,
                'assertGreaterThanOrEqual',
                'assertLessThanOrEqual'
            ),
            new BinaryOpWithAssertMethod(
                SmallerOrEqual::class,
                'assertLessThanOrEqual',
                'assertGreaterThanOrEqual'
            ),
        ];
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns comparison operations to their method name alternatives in PHPUnit TestCase',
            [
                new CodeSample(
                    '$this->assertTrue($foo === $bar, "message");',
                    '$this->assertSame($bar, $foo, "message");'
                ),
                new CodeSample(
                    '$this->assertFalse($foo >= $bar, "message");',
                    '$this->assertLessThanOrEqual($bar, $foo, "message");'
                ),
            ]
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
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($node, ['assertTrue', 'assertFalse'])) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        $firstArgumentValue = $node->getArgs()[0]
            ->value;
        if (! $firstArgumentValue instanceof BinaryOp) {
            return null;
        }

        return $this->processCallWithBinaryOp($node, $firstArgumentValue);
    }

    private function processCallWithBinaryOp(MethodCall|StaticCall $node, BinaryOp $binaryOp): ?Node
    {
        $binaryOpClass = $binaryOp::class;

        foreach ($this->binaryOpWithAssertMethods as $binaryOpWithAssertMethod) {
            if ($binaryOpClass !== $binaryOpWithAssertMethod->getBinaryOpClass()) {
                continue;
            }

            $this->identifierManipulator->renameNodeWithMap($node, [
                'assertTrue' => $binaryOpWithAssertMethod->getAssetMethodName(),
                'assertFalse' => $binaryOpWithAssertMethod->getNotAssertMethodName(),
            ]);

            $this->changeArgumentsOrder($node);

            return $node;
        }

        return null;
    }

    private function changeArgumentsOrder(MethodCall|StaticCall $node): void
    {
        $oldArguments = $node->getArgs();

        /** @var BinaryOp $expression */
        $expression = $oldArguments[0]->value;

        if ($this->isConstantValue($expression->left)) {
            $firstArgument = new Arg($expression->left);
            $secondArgument = new Arg($expression->right);
        } else {
            $firstArgument = new Arg($expression->right);
            $secondArgument = new Arg($expression->left);
        }

        unset($oldArguments[0]);
        $newArgs = [$firstArgument, $secondArgument];
        $node->args = [...$newArgs, ...$oldArguments];
    }

    private function isConstantValue(Expr $expr): bool
    {
        $staticType = $this->nodeTypeResolver->getType($expr);
        if ($staticType instanceof ConstantScalarType) {
            return true;
        }

        return $staticType instanceof ConstantArrayType;
    }
}
