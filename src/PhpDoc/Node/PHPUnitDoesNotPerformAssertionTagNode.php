<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PhpDoc\Node;

use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;

/**
 * @see \Rector\PHPUnit\PhpDoc\NodeFactory\PHPUnitDataDoesNotPerformAssertionDocNodeFactory
 */
final class PHPUnitDoesNotPerformAssertionTagNode extends PhpDocTagNode
{
    /**
     * @var string
     */
    public const NAME = '@doesNotPerformAssertions';

    public function __construct()
    {
        parent::__construct(self::NAME, new GenericTagValueNode(''));
    }
}
