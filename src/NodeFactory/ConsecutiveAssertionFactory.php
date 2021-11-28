<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\ArrayItem;
use PhpParser\Node\Expr\ConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\New_;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Name;
use PhpParser\Node\Name\FullyQualified;
use Rector\PHPUnit\ValueObject\ExpectationMock;
use Rector\PHPUnit\ValueObject\ExpectationMockCollection;

final class ConsecutiveAssertionFactory
{
    /**
     * @var array<string, string>
     */
    private const REPLACE_WILL_MAP = [
        'willReturnMap' => 'returnValueMap',
        'willReturnArgument' => 'returnArgument',
        'willReturnCallback' => 'returnCallback',
        'willThrowException' => 'throwException',
    ];

    public function createAssertionFromExpectationMockCollection(
        ExpectationMockCollection $expectationMockCollection
    ): MethodCall {
        $expectationMocks = $expectationMockCollection->getExpectationMocks();

        $variable = $expectationMocks[0]->getExpectationVariable();
        $methodArguments = $expectationMocks[0]->getMethodArguments();

        $expectationMocks = $this->sortExpectationMocksByIndex($expectationMocks);

        if (! $expectationMockCollection->hasReturnValues()) {
            return $this->createWithConsecutive(
                $this->createMethod($variable, $methodArguments),
                $this->createWithArgs($expectationMocks)
            );
        }

        if ($expectationMockCollection->hasWithValues()) {
            return $this->createWillReturnOnConsecutiveCalls(
                $this->createWithConsecutive(
                    $this->createMethod($variable, $methodArguments),
                    $this->createWithArgs($expectationMocks)
                ),
                $this->createReturnArgs($expectationMocks)
            );
        }

        return $this->createWillReturnOnConsecutiveCalls(
            $this->createMethod($variable, $methodArguments),
            $this->createReturnArgs($expectationMocks)
        );
    }

    /**
     * @param Arg[] $args
     */
    public function createWillReturnOnConsecutiveCalls(Expr $expr, array $args): MethodCall
    {
        return $this->createMethodCall($expr, 'willReturnOnConsecutiveCalls', $args);
    }

    /**
     * @param Arg[] $args
     */
    public function createMethod(Expr $expr, array $args): MethodCall
    {
        return $this->createMethodCall($expr, 'method', $args);
    }

    /**
     * @param Arg[] $args
     */
    public function createWithConsecutive(Expr $expr, array $args): MethodCall
    {
        return $this->createMethodCall($expr, 'withConsecutive', $args);
    }

    public function createWillReturn(MethodCall $methodCall): Expr
    {
        if (! $methodCall->name instanceof Identifier) {
            return $methodCall;
        }

        $methodCallName = $methodCall->name->name;
        if ($methodCallName === 'will') {
            return $methodCall->args[0]->value;
        }

        if ($methodCallName === 'willReturnSelf') {
            return $this->createWillReturnSelf();
        }

        if ($methodCallName === 'willReturnReference') {
            return $this->createWillReturnReference($methodCall);
        }

        if (array_key_exists($methodCallName, self::REPLACE_WILL_MAP)) {
            return $this->createMappedWillReturn($methodCallName, $methodCall);
        }

        return $methodCall->args[0]->value;
    }

    /**
     * @param ExpectationMock[] $expectationMocks
     * @return Arg[]
     */
    private function createReturnArgs(array $expectationMocks): array
    {
        return array_map(
            static fn (ExpectationMock $expectationMock): Arg => new Arg(
                $expectationMock->getReturn() instanceof Expr ? $expectationMock->getReturn() : new ConstFetch(new Name(
                    'null'
                ))
            ),
            $expectationMocks
        );
    }

    /**
     * @param ExpectationMock[] $expectationMocks
     * @return Arg[]
     */
    private function createWithArgs(array $expectationMocks): array
    {
        return array_map(static function (ExpectationMock $expectationMock): Arg {
            $arrayItems = array_map(
                static fn (?Expr $expr): ArrayItem => new ArrayItem($expr instanceof Expr ? $expr : new ConstFetch(
                    new Name('null')
                )),
                $expectationMock->getWithArguments()
            );
            return new Arg(new Array_($arrayItems));
        }, $expectationMocks);
    }

    private function createWillReturnSelf(): MethodCall
    {
        return $this->createMethodCall(new Variable('this'), 'returnSelf', []);
    }

    private function createWillReturnReference(MethodCall $methodCall): New_
    {
        return new New_(
            new FullyQualified('PHPUnit\Framework\MockObject\Stub\ReturnReference'),
            [new Arg($methodCall->args[0]->value)]
        );
    }

    private function createMappedWillReturn(string $methodCallName, MethodCall $methodCall): MethodCall
    {
        return $this->createMethodCall(
            new Variable('this'),
            self::REPLACE_WILL_MAP[$methodCallName],
            [new Arg($methodCall->args[0]->value)]
        );
    }

    /**
     * @param Arg[] $args
     */
    private function createMethodCall(Expr $expr, string $name, array $args): MethodCall
    {
        return new MethodCall($expr, new Identifier($name), $args);
    }

    /**
     * @param ExpectationMock[] $expectationMocks
     * @return ExpectationMock[]
     */
    private function sortExpectationMocksByIndex(array $expectationMocks): array
    {
        usort(
            $expectationMocks,
            static fn (ExpectationMock $expectationMockA, ExpectationMock $expectationMockB): int => $expectationMockA->getIndex() > $expectationMockB->getIndex() ? 1 : -1
        );
        return $expectationMocks;
    }
}
