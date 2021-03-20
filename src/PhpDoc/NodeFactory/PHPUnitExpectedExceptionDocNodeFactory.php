<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PhpDoc\NodeFactory;

use PHPStan\PhpDocParser\Ast\Node;
use PHPStan\PhpDocParser\Parser\TokenIterator;
use PHPStan\PhpDocParser\Parser\TypeParser;
use Rector\BetterPhpDocParser\Contract\StringTagMatchingPhpDocNodeFactoryInterface;
use Rector\PHPUnit\PhpDoc\Node\PHPUnitExpectedExceptionTagValueNode;

final class PHPUnitExpectedExceptionDocNodeFactory implements StringTagMatchingPhpDocNodeFactoryInterface
{
    /**
     * @var TypeParser
     */
    private $typeParser;

    public function __construct(TypeParser $typeParser)
    {
        $this->typeParser = $typeParser;
    }

    public function createFromTokens(TokenIterator $tokenIterator): ?Node
    {
        $type = $this->typeParser->parse($tokenIterator);
        return new PHPUnitExpectedExceptionTagValueNode($type);
    }

    public function match(string $tag): bool
    {
        return strtolower($tag) === strtolower(PHPUnitExpectedExceptionTagValueNode::NAME);
    }
}
