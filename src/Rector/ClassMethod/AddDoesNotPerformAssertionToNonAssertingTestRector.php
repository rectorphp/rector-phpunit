<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\Type\TypeWithClassName;
use Rector\Core\PhpParser\AstResolver;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see https://phpunit.readthedocs.io/en/7.3/annotations.html#doesnotperformassertions
 * @see https://github.com/sebastianbergmann/phpunit/issues/2484
 *
 * @see \Rector\PHPUnit\Tests\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\AddDoesNotPerformAssertionToNonAssertingTestRectorTest
 */
final class AddDoesNotPerformAssertionToNonAssertingTestRector extends AbstractRector
{
    /**
     * @var int
     */
    private const MAX_LOOKING_FOR_ASSERT_METHOD_CALL_NESTING_LEVEL = 3;

    /**
     * This should prevent segfaults while going too deep into to parsed code. Without it, it might end-up with segfault
     *
     * @var int
     */
    private $classMethodNestingLevel = 0;

    /**
     * @var bool[]
     */
    private $containsAssertCallByClassMethod = [];

    public function __construct(
        private TestsNodeAnalyzer $testsNodeAnalyzer,
        private AstResolver $astResolver
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Tests without assertion will have @doesNotPerformAssertion',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeClass extends TestCase
{
    public function test()
    {
        $nothing = 5;
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeClass extends TestCase
{
    /**
     * @doesNotPerformAssertions
     */
    public function test()
    {
        $nothing = 5;
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [ClassMethod::class];
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        $this->classMethodNestingLevel = 0;

        if ($this->shouldSkipClassMethod($node)) {
            return null;
        }

        $this->addDoesNotPerformAssertions($node);

        return $node;
    }

    private function shouldSkipClassMethod(ClassMethod $classMethod): bool
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($classMethod)) {
            return true;
        }

        if (! $this->testsNodeAnalyzer->isTestClassMethod($classMethod)) {
            return true;
        }

        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        if ($phpDocInfo->hasByNames(['doesNotPerformAssertions', 'expectedException'])) {
            return true;
        }

        return $this->containsAssertCall($classMethod);
    }

    private function addDoesNotPerformAssertions(ClassMethod $classMethod): void
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $phpDocInfo->addPhpDocTagNode(new PhpDocTagNode('@doesNotPerformAssertions', new GenericTagValueNode('')));
    }

    private function containsAssertCall(ClassMethod $classMethod): bool
    {
        ++$this->classMethodNestingLevel;

        // probably no assert method in the end
        if ($this->classMethodNestingLevel > self::MAX_LOOKING_FOR_ASSERT_METHOD_CALL_NESTING_LEVEL) {
            return false;
        }

        $cacheHash = md5($this->print($classMethod));
        if (isset($this->containsAssertCallByClassMethod[$cacheHash])) {
            return $this->containsAssertCallByClassMethod[$cacheHash];
        }

        // A. try "->assert" shallow search first for performance
        $hasDirectAssertCall = $this->hasDirectAssertCall($classMethod);
        if ($hasDirectAssertCall) {
            $this->containsAssertCallByClassMethod[$cacheHash] = $hasDirectAssertCall;
            return true;
        }

        // B. look for nested calls
        $hasNestedAssertCall = $this->hasNestedAssertCall($classMethod);
        $this->containsAssertCallByClassMethod[$cacheHash] = $hasNestedAssertCall;

        return $hasNestedAssertCall;
    }

    private function hasDirectAssertCall(ClassMethod $classMethod): bool
    {
        return (bool) $this->betterNodeFinder->findFirst((array) $classMethod->stmts, function (Node $node): bool {
            if ($node instanceof MethodCall) {
                return $this->isNames($node->name, [
                    // phpunit
                    '*assert',
                    'assert*',
                    'expectException*',
                    'setExpectedException*',
                ]);
            }
            if ($node instanceof StaticCall) {
                return $this->isNames($node->name, [
                    // phpunit
                    '*assert',
                    'assert*',
                    'expectException*',
                    'setExpectedException*',
                ]);
            }
            return false;
        });
    }

    private function hasNestedAssertCall(ClassMethod $classMethod): bool
    {
        $currentClassMethod = $classMethod;

        // over and over the same method :/
        return (bool) $this->betterNodeFinder->findFirst((array) $classMethod->stmts, function (Node $node) use (
            $currentClassMethod
        ): bool {
            if (! $node instanceof MethodCall && ! $node instanceof StaticCall) {
                return false;
            }

            $classMethod = $this->resolveClassMethodFromCall($node);

            // skip circular self calls
            if ($currentClassMethod === $classMethod) {
                return false;
            }

            if ($classMethod !== null) {
                return $this->containsAssertCall($classMethod);
            }

            return false;
        });
    }

    private function resolveClassMethodFromCall(StaticCall | MethodCall $call): ?ClassMethod
    {
        if ($call instanceof MethodCall) {
            $objectType = $this->getObjectType($call->var);
        } else {
            // StaticCall
            $objectType = $this->getObjectType($call->class);
        }

        if (! $objectType instanceof TypeWithClassName) {
            return null;
        }

        $methodName = $this->getName($call->name);
        if ($methodName === null) {
            return null;
        }

        return $this->astResolver->resolveClassMethod($objectType->getClassName(), $methodName);
    }
}
