<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

use PhpParser\Node\Expr;
use PhpParser\Node\Expr\CallLike;
use PhpParser\Node\Expr\Match_;
use Rector\Exception\ShouldNotHappenException;

final readonly class MatchAndReturnMatch
{
    public function __construct(
        private Match_ $consecutiveMatch,
        private ?Match_ $willReturnMatch
    ) {
    }

    public function getConsecutiveMatch(): Match_
    {
        return $this->consecutiveMatch;
    }

    public function getConsecutiveMatchExpr(): Expr
    {
        $soleArm = $this->consecutiveMatch->arms[0];
        if ($soleArm->body instanceof CallLike) {
            $assertCall = $soleArm->body;
            $firstArg = $assertCall->getArgs()[0];
            return $firstArg->value;
        }

        throw new ShouldNotHappenException();
    }

    public function getWillReturnMatch(): ?Match_
    {
        return $this->willReturnMatch;
    }

    public function getWillReturnMatchExpr(): Expr
    {
        if (! $this->willReturnMatch instanceof Match_) {
            throw new ShouldNotHappenException();
        }

        $soleArm = $this->willReturnMatch->arms[0];
        return $soleArm->body;
    }
}
