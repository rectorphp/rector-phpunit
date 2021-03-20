<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PhpDoc\NodeFactory;

use PHPStan\PhpDocParser\Ast\Node;
use PHPStan\PhpDocParser\Parser\TokenIterator;
use Rector\BetterPhpDocParser\Contract\StringTagMatchingPhpDocNodeFactoryInterface;
use Rector\PHPUnit\PhpDoc\Node\PHPUnitDoesNotPerformAssertionTagNode;

final class PHPUnitDataDoesNotPerformAssertionDocNodeFactory implements StringTagMatchingPhpDocNodeFactoryInterface
{
    public function createFromTokens(TokenIterator $tokenIterator): ?Node
    {
        return new PHPUnitDoesNotPerformAssertionTagNode();
    }

    public function match(string $tag): bool
    {
        return strtolower($tag) === strtolower(PHPUnitDoesNotPerformAssertionTagNode::NAME);
    }
}
