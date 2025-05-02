<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Enum;

final class NonStaticNonAssertPrefixedAssertionMethods
{
    /**
     * @var string[]
     */
    public const ALL = [
        'createMock',
        'atLeast',
        'atLeastOnce',
        'once',
        'never',
        'expectException',
        'expectExceptionMessage',
        'expectExceptionCode',
        'expectExceptionMessageMatches',
    ];
}
