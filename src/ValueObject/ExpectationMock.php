<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt\Expression;

final class ExpectationMock
{
    /**
     * @param Variable|PropertyFetch $expectationVariable
     * @param Arg[] $methodArguments
     * @param array<int, null|Expr> $withArguments
     */
    public function __construct(
        private Expr $expectationVariable,
        private array $methodArguments,
        private int $index,
        private ?\PhpParser\Node\Expr $expr,
        private array $withArguments,
        private ?\PhpParser\Node\Stmt\Expression $originalExpression
    ) {
    }

    /**
     * @return Variable|PropertyFetch
     */
    public function getExpectationVariable(): Expr
    {
        return $this->expectationVariable;
    }

    /**
     * @return Arg[]
     */
    public function getMethodArguments(): array
    {
        return $this->methodArguments;
    }

    public function getIndex(): int
    {
        return $this->index;
    }

    public function getReturn(): ?Expr
    {
        return $this->expr;
    }

    /**
     * @return array<int, null|Expr>
     */
    public function getWithArguments(): array
    {
        return $this->withArguments;
    }

    public function getOriginalExpression(): ?Expression
    {
        return $this->originalExpression;
    }
}
