<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\Empty_;
use PhpParser\Node\Expr\FuncCall;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use PHPStan\Type\StringType;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\ValueObject\FunctionNameWithAssertMethods;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\AssertTrueFalseToSpecificMethodRectorTest
 */
final class AssertTrueFalseToSpecificMethodRector extends AbstractRector
{
    /**
     * @var FunctionNameWithAssertMethods[]
     */
    private array $functionNameWithAssertMethods = [];

    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
        $this->functionNameWithAssertMethods = [
            'is_readable' => new FunctionNameWithAssertMethods(
                'is_readable',
                'assertIsReadable',
                'assertNotIsReadable'
            ),
            'array_key_exists' => new FunctionNameWithAssertMethods(
                'array_key_exists',
                'assertArrayHasKey',
                'assertArrayNotHasKey'
            ),
            'array_search' => new FunctionNameWithAssertMethods('array_search', 'assertContains', 'assertNotContains'),
            'in_array' => new FunctionNameWithAssertMethods('in_array', 'assertContains', 'assertNotContains'),
            'empty' => new FunctionNameWithAssertMethods('empty', 'assertEmpty', 'assertNotEmpty'),
            'file_exists' => new FunctionNameWithAssertMethods(
                'file_exists',
                'assertFileExists',
                'assertFileNotExists'
            ),
            'is_dir' => new FunctionNameWithAssertMethods(
                'is_dir',
                'assertDirectoryExists',
                'assertDirectoryNotExists'
            ),
            'is_infinite' => new FunctionNameWithAssertMethods('is_infinite', 'assertInfinite', 'assertFinite'),
            'is_null' => new FunctionNameWithAssertMethods('is_null', 'assertNull', 'assertNotNull'),
            'is_writable' => new FunctionNameWithAssertMethods(
                'is_writable',
                'assertIsWritable',
                'assertNotIsWritable'
            ),
            'is_nan' => new FunctionNameWithAssertMethods('is_nan', 'assertNan', ''),
            'is_a' => new FunctionNameWithAssertMethods('is_a', 'assertInstanceOf', 'assertNotInstanceOf'),
        ];
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns true/false comparisons to their method name alternatives in PHPUnit TestCase when possible',
            [
                new CodeSample(
                    '$this->assertTrue(is_readable($readmeFile), "message");',
                    '$this->assertIsReadable($readmeFile, "message");'
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
            ['assertTrue', 'assertFalse', 'assertNotTrue', 'assertNotFalse']
        )) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        $arguments = $node->getArgs();
        if ($arguments === []) {
            return null;
        }

        $firstArgumentValue = $arguments[0]->value;
        if (! $firstArgumentValue instanceof FuncCall && ! $firstArgumentValue instanceof Empty_) {
            return null;
        }

        $firstArgumentName = $this->getName($firstArgumentValue);
        if ($firstArgumentName === null || ! array_key_exists(
            $firstArgumentName,
            $this->functionNameWithAssertMethods
        )) {
            return null;
        }

        $functionNameWithAssertMethod = $this->functionNameWithAssertMethods[$firstArgumentName];
        if ($firstArgumentName === 'is_a') {
            /**
             * @var FuncCall $firstArgumentValue
             * @var array<Arg> $args
             **/
            $args = $firstArgumentValue->getArgs();
            if ($args === []) {
                return null;
            }

            $firstArgumentType = $this->nodeTypeResolver->getType($args[0]->value);
            if ($firstArgumentType instanceof StringType) {
                return null;
            }
        }

        $this->renameMethod($node, $functionNameWithAssertMethod);
        $this->moveFunctionArgumentsUp($node);

        return $node;
    }

    private function renameMethod(
        MethodCall|StaticCall $node,
        FunctionNameWithAssertMethods $functionNameWithAssertMethods
    ): void {
        /** @var Identifier $identifierNode */
        $identifierNode = $node->name;
        $oldMethodName = $identifierNode->toString();

        if (in_array($oldMethodName, ['assertTrue', 'assertNotFalse'], true)) {
            $node->name = new Identifier($functionNameWithAssertMethods->getAssetMethodName());
        }

        if ($functionNameWithAssertMethods->getNotAssertMethodName() === '') {
            return;
        }

        if (! in_array($oldMethodName, ['assertFalse', 'assertNotTrue'], true)) {
            return;
        }

        $node->name = new Identifier($functionNameWithAssertMethods->getNotAssertMethodName());
    }

    /**
     * Before:
     * - $this->assertTrue(array_key_exists('...', ['...']), 'second argument');
     *
     * After:
     * - $this->assertArrayHasKey('...', ['...'], 'second argument');
     */
    private function moveFunctionArgumentsUp(MethodCall|StaticCall $node): void
    {
        $funcCallOrEmptyNode = $node->getArgs()[0]
->value;

        if ($funcCallOrEmptyNode instanceof FuncCall) {
            $funcCallOrEmptyNodeName = $this->getName($funcCallOrEmptyNode);
            if ($funcCallOrEmptyNodeName === null) {
                return;
            }

            $funcCallOrEmptyNodeArgs = $funcCallOrEmptyNode->getArgs();
            $oldArguments = $node->getArgs();
            unset($oldArguments[0]);

            $node->args = $this->buildNewArguments(
                $funcCallOrEmptyNodeName,
                $funcCallOrEmptyNodeArgs,
                $oldArguments
            );
        }

        if ($funcCallOrEmptyNode instanceof Empty_) {
            $node->args[0] = new Arg($funcCallOrEmptyNode->expr);
        }
    }

    /**
     * @param Arg[] $funcCallOrEmptyNodeArgs
     * @param Arg[] $oldArguments
     * @return mixed[]
     */
    private function buildNewArguments(
        string $funcCallOrEmptyNodeName,
        array $funcCallOrEmptyNodeArgs,
        array $oldArguments
    ): array {
        if (in_array($funcCallOrEmptyNodeName, ['in_array', 'array_search'], true)
            && count($funcCallOrEmptyNodeArgs) === 3) {
            unset($funcCallOrEmptyNodeArgs[2]);

            return $this->appendArgs($funcCallOrEmptyNodeArgs, $oldArguments);
        }

        if ($funcCallOrEmptyNodeName === 'is_a') {
            $newArgs = [$funcCallOrEmptyNodeArgs[1], $funcCallOrEmptyNodeArgs[0]];

            return $this->appendArgs($newArgs, $oldArguments);
        }

        return $this->appendArgs($funcCallOrEmptyNodeArgs, $oldArguments);
    }
}
