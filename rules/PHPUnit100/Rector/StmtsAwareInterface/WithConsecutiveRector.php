<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit100\Rector\StmtsAwareInterface;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Param;
use PhpParser\Node\Scalar\LNumber;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Return_;
use PhpParser\Node\Stmt\Throw_;
use Rector\Exception\ShouldNotHappenException;
use Rector\PHPUnit\Enum\ConsecutiveMethodName;
use Rector\PHPUnit\Enum\ConsecutiveVariable;
use Rector\PHPUnit\MethodCallRemover;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFinder\MethodCallNodeFinder;
use Rector\PHPUnit\PHPUnit100\NodeDecorator\WillReturnIfNodeDecorator;
use Rector\PHPUnit\PHPUnit100\NodeFactory\WillReturnCallbackFactory;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\WithConsecutiveRectorTest
 */
final class WithConsecutiveRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly WillReturnCallbackFactory $willReturnCallbackFactory,
<<<<<<< HEAD
<<<<<<< HEAD
=======
        private readonly ConsecutiveIfsFactory $consecutiveIfsFactory,
>>>>>>> f9d5473 (extract WillReturnPerIfNodeDecorator)
        private readonly WillReturnPerIfNodeDecorator $willReturnPerIfNodeDecorator,
        private readonly MethodCallNodeFinder $methodCallNodeFinder,
        private readonly ExpectsMethodCallDecorator $expectsMethodCallDecorator,
<<<<<<< HEAD
        private readonly MethodCallRemover $methodCallRemover
=======
        private readonly \Rector\PHPUnit\MethodCallRemover $methodCallRemover
>>>>>>> 320f0bc (extract method call remoiver)
=======
        private readonly WillReturnIfNodeDecorator $willReturnPerIfNodeDecorator,
        private readonly MethodCallNodeFinder $methodCallNodeFinder,
        private readonly ExpectsMethodCallDecorator $expectsMethodCallDecorator,
        private readonly MethodCallRemover $methodCallRemover
>>>>>>> e2766a6 (single return stmt)
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Refactor deprecated withConsecutive() to willReturnCallback() structure', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            );
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(function (...$parameters) use ($matcher) {
                if ($matcher->numberOfInvocations() === 1) {
                    self::assertEquals([1, 2], $parameters);
                }

                if ($matcher->numberOfInvocations() === 2) {
                    self::assertEquals([3, 4], $parameters),
                };
            });
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
        return [Expression::class];
    }

    /**
     * @param Expression $node
     */
    public function refactor(Node $node)
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $withConsecutiveMethodCall = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WITH_CONSECUTIVE
        );
        if (! $withConsecutiveMethodCall instanceof MethodCall) {
            return null;
        }

        if ($this->methodCallNodeFinder->hasByNames($node, ['willReturnMap', 'will'])) {
            return null;
        }

        $returnStmt = null;

        $willReturn = $this->methodCallNodeFinder->findByName($node, ConsecutiveMethodName::WILL_RETURN);
        if ($willReturn instanceof MethodCall) {
<<<<<<< HEAD
<<<<<<< HEAD
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN);
            $expr = $this->getFirstArgValue($willReturn);
            $returnStmt = new Return_($expr);
<<<<<<< HEAD
=======
            $this->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN);
=======
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN);
>>>>>>> 320f0bc (extract method call remoiver)
            $expr = $this->getFirstArgValue($willReturn);
            $returnStmts[] = new Return_($expr);
>>>>>>> 9a6e06d (narrow)
=======
>>>>>>> e2766a6 (single return stmt)
        }

        $willReturnSelf = $this->methodCallNodeFinder->findByName($node, ConsecutiveMethodName::WILL_RETURN_SELF);
        if ($willReturnSelf instanceof MethodCall) {
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_SELF);
<<<<<<< HEAD
<<<<<<< HEAD
            $returnStmt = $this->createWillReturnSelfStmts($willReturnSelf);
=======
            $returnStmts[] = $this->createWillReturnSelfStmts($willReturnSelf);
>>>>>>> 320f0bc (extract method call remoiver)
=======
            $returnStmt = $this->createWillReturnSelfStmts($willReturnSelf);
>>>>>>> e2766a6 (single return stmt)
        }

        $willReturnArgument = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WILL_RETURN_ARGUMENT
        );
        if ($willReturnArgument instanceof MethodCall) {
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_ARGUMENT);
<<<<<<< HEAD
<<<<<<< HEAD
            $returnStmt = $this->createWillReturnArgument($willReturnArgument);
=======
            $returnStmts[] = $this->createWillReturnArgument($willReturnArgument);
>>>>>>> 320f0bc (extract method call remoiver)
=======
            $returnStmt = $this->createWillReturnArgument($willReturnArgument);
>>>>>>> e2766a6 (single return stmt)
        }

        $willReturnOnConsecutiveMethodCall = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WILL_RETURN_ON_CONSECUTIVE_CALLS,
        );

<<<<<<< HEAD
<<<<<<< HEAD
        if ($willReturnOnConsecutiveMethodCall instanceof MethodCall) {
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_ON_CONSECUTIVE_CALLS);
=======
        if ($willReturnOnConsecutiveCallsArgument instanceof MethodCall) {
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_ON_CONSECUTIVE_CALLS);

            $returnStmts = $this->consecutiveIfsFactory->createCombinedIfs(
                $withConsecutiveMethodCall,
                $willReturnOnConsecutiveCallsArgument
            );

            $areIfsPreferred = true;
>>>>>>> 320f0bc (extract method call remoiver)
=======
        if ($willReturnOnConsecutiveMethodCall instanceof MethodCall) {
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_ON_CONSECUTIVE_CALLS);
>>>>>>> f9d5473 (extract WillReturnPerIfNodeDecorator)
        }

        $willThrowException = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WILL_THROW_EXCEPTION
        );
        if ($willThrowException instanceof MethodCall) {
<<<<<<< HEAD
<<<<<<< HEAD
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_THROW_EXCEPTION);
            $expr = $this->getFirstArgValue($willThrowException);
            $returnStmt = new Throw_($expr);
<<<<<<< HEAD
=======
            $this->removeMethodCall($node, ConsecutiveMethodName::WILL_THROW_EXCEPTION);
=======
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_THROW_EXCEPTION);
>>>>>>> 320f0bc (extract method call remoiver)
            $expr = $this->getFirstArgValue($willThrowException);
            $returnStmts[] = new Throw_($expr);
>>>>>>> 9a6e06d (narrow)
=======
>>>>>>> e2766a6 (single return stmt)
        }

        $willReturnReferenceArgument = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WILL_RETURN_REFERENCE
        );

        $referenceVariable = null;
        if ($willReturnReferenceArgument instanceof MethodCall) {
<<<<<<< HEAD
<<<<<<< HEAD
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_REFERENCE);
            $expr = $this->getFirstArgValue($willReturnReferenceArgument);
            $returnStmt = new Return_($expr);
<<<<<<< HEAD
=======
            $this->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_REFERENCE);
=======
            $this->methodCallRemover->removeMethodCall($node, ConsecutiveMethodName::WILL_RETURN_REFERENCE);
>>>>>>> 320f0bc (extract method call remoiver)
            $expr = $this->getFirstArgValue($willReturnReferenceArgument);
            $returnStmts[] = new Return_($expr);
>>>>>>> 9a6e06d (narrow)
=======
>>>>>>> e2766a6 (single return stmt)

            // returns passed args
            $referenceVariable = new Variable('parameters');
        }

        $expectsCall = $this->expectsMethodCallDecorator->decorate($node);

        if (! $expectsCall instanceof MethodCall && ! $expectsCall instanceof StaticCall) {
            // fallback to default by case count
            $lNumber = new LNumber(\count($withConsecutiveMethodCall->args));
            $expectsCall = new MethodCall(new Variable('this'), new Identifier('exactly'), [new Arg($lNumber)]);
        }

        // 2. does willReturnCallback() exist? just merge them together
        $existingWillReturnCallback = $this->methodCallNodeFinder->findByName(
            $node,
            ConsecutiveMethodName::WILL_RETURN_CALLBACK
        );
        if ($existingWillReturnCallback instanceof MethodCall) {
            return $this->refactorWithExistingWillReturnCallback(
                $existingWillReturnCallback,
                $withConsecutiveMethodCall,
                $node
            );
        }

        // 3. rename and replace withConsecutive()
        return $this->refactorToWillReturnCallback(
            $withConsecutiveMethodCall,
            $returnStmt,
            $referenceVariable,
            $expectsCall,
            $node,
            $willReturnOnConsecutiveMethodCall
        );
    }

    /**
     * @return Stmt[]
     */
    private function refactorToWillReturnCallback(
        MethodCall $withConsecutiveMethodCall,
        ?Stmt $returnStmt,
        Expr|Variable|null $referenceVariable,
        StaticCall|MethodCall $expectsCall,
        Expression $expression,
        ?MethodCall $willReturnOnConsecutiveMethodCall
    ): array {
        $closure = $this->willReturnCallbackFactory->createClosure(
            $withConsecutiveMethodCall,
            $returnStmt,
            $referenceVariable,
        );

        $withConsecutiveMethodCall->name = new Identifier(ConsecutiveMethodName::WILL_RETURN_CALLBACK);
        $withConsecutiveMethodCall->args = [new Arg($closure)];

        $matcherVariable = new Variable(ConsecutiveVariable::MATCHER);
        $matcherAssign = new Assign($matcherVariable, $expectsCall);

        $this->willReturnPerIfNodeDecorator->decorate($closure, $willReturnOnConsecutiveMethodCall);

        return [new Expression($matcherAssign), $expression];
    }

    private function refactorWithExistingWillReturnCallback(
        MethodCall $existingWillReturnCallback,
        MethodCall $withConsecutiveMethodCall,
        Expression $expression
    ): Expression {
        $callbackArg = $existingWillReturnCallback->getArgs()[0];
        if (! $callbackArg->value instanceof Closure) {
            throw new ShouldNotHappenException();
        }

        $callbackClosure = $callbackArg->value;
        $callbackClosure->params[] = new Param(new Variable(ConsecutiveVariable::PARAMETERS));

        $parametersMatch = $this->willReturnCallbackFactory->createParametersMatch($withConsecutiveMethodCall);
        $callbackClosure->stmts = array_merge($parametersMatch, $callbackClosure->stmts);

        $this->methodCallRemover->removeMethodCall($expression, ConsecutiveMethodName::WITH_CONSECUTIVE);

        return $expression;
    }

<<<<<<< HEAD
<<<<<<< HEAD
=======
    private function removeMethodCall(Expression $expression, string $methodName): void
    {
        $this->traverseNodesWithCallable($expression, function (Node $node) use ($methodName): ?Node {
            if (! $node instanceof MethodCall) {
                return null;
            }

            if (! $this->isName($node->name, $methodName)) {
                return null;
            }

            return $node->var;
        });
    }

>>>>>>> 9a6e06d (narrow)
=======
>>>>>>> 320f0bc (extract method call remoiver)
    private function createWillReturnSelfStmts(MethodCall $willReturnSelfMethodCall): Return_
    {
        $selfVariable = $willReturnSelfMethodCall;
        while (true) {
            if (! $selfVariable instanceof MethodCall) {
                break;
            }

            $selfVariable = $selfVariable->var;
        }

        return new Return_($selfVariable);
    }

    private function createWillReturnArgument(MethodCall $willReturnArgumentMethodCall): Return_
    {
        $parametersVariable = new Variable(ConsecutiveVariable::PARAMETERS);

        $expr = $this->getFirstArgValue($willReturnArgumentMethodCall);
        return new Return_(new ArrayDimFetch($parametersVariable, $expr));
    }

    private function getFirstArgValue(MethodCall $methodCall): Expr
    {
        $firstArg = $methodCall->getArgs()[0] ?? null;
        if (! $firstArg instanceof Arg) {
            throw new ShouldNotHappenException();
        }

        return $firstArg->value;
    }
}
