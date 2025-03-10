<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\FuncCall;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use Rector\Configuration\Deprecation\Contract\DeprecatedInterface;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\ValueObject\FunctionNameWithAssertMethods;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @deprecated This rule is deprecated, as its logic is handled better
 * by other smaller rules in phpunit-code-quality set
 */
final class AssertCompareToSpecificMethodRector extends AbstractRector implements DeprecatedInterface
{
    /**
     * @var string
     */
    private const ASSERT_COUNT = 'assertCount';

    /**
     * @var string
     */
    private const ASSERT_NOT_COUNT = 'assertNotCount';

    /**
     * @var FunctionNameWithAssertMethods[]
     */
    private array $functionNamesWithAssertMethods = [];

    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
        $this->functionNamesWithAssertMethods = [
            new FunctionNameWithAssertMethods('count', self::ASSERT_COUNT, self::ASSERT_NOT_COUNT),
            new FunctionNameWithAssertMethods('sizeof', self::ASSERT_COUNT, self::ASSERT_NOT_COUNT),
            new FunctionNameWithAssertMethods('iterator_count', self::ASSERT_COUNT, self::ASSERT_NOT_COUNT),
            new FunctionNameWithAssertMethods('get_class', 'assertInstanceOf', 'assertNotInstanceOf'),
        ];
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns vague php-only method in PHPUnit TestCase to more specific',
            [
                new CodeSample(
                    '$this->assertSame(10, count($anything), "message");',
                    '$this->assertCount(10, $anything, "message");'
                ),
                new CodeSample(
                    '$this->assertNotEquals(SomeInstance::class, get_class($value));',
                    '$this->assertNotInstanceOf(SomeInstance::class, $value);'
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
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames(
            $node,
            ['assertSame', 'assertNotSame', 'assertEquals', 'assertNotEquals']
        )) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        // we need 2 args
        if (! isset($node->args[1])) {
            return null;
        }

        $firstArgument = $node->getArgs()[0];
        $secondArgument = $node->getArgs()[1];
        $secondArgumentValue = $secondArgument->value;

        if ($secondArgumentValue instanceof FuncCall) {
            return $this->processFuncCallArgumentValue($node, $secondArgumentValue, $firstArgument);
        }

        return null;
    }

    /**
     * @return MethodCall|StaticCall|null
     */
    private function processFuncCallArgumentValue(
        MethodCall|StaticCall $node,
        FuncCall $funcCall,
        Arg $requiredArg
    ): ?Node {
        foreach ($this->functionNamesWithAssertMethods as $functionNameWithAssertMethod) {
            if (! $this->isName($funcCall, $functionNameWithAssertMethod->getFunctionName())) {
                continue;
            }

            $this->renameMethod($node, $functionNameWithAssertMethod);
            $this->moveFunctionArgumentsUp($node, $funcCall, $requiredArg);

            return $node;
        }

        return null;
    }

    private function renameMethod(
        MethodCall|StaticCall $node,
        FunctionNameWithAssertMethods $functionNameWithAssertMethods
    ): void {
        if ($this->isNames($node->name, ['assertSame', 'assertEquals'])) {
            $node->name = new Identifier($functionNameWithAssertMethods->getAssetMethodName());
        } elseif ($this->isNames($node->name, ['assertNotSame', 'assertNotEquals'])) {
            $node->name = new Identifier($functionNameWithAssertMethods->getNotAssertMethodName());
        }
    }

    /**
     * Handles custom error messages to not be overwrite by function with multiple args.
     */
    private function moveFunctionArgumentsUp(StaticCall|MethodCall $node, FuncCall $funcCall, Arg $requiredArg): void
    {
        $node->args[1] = $funcCall->getArgs()[0];
        $node->args[0] = $requiredArg;
    }
}
