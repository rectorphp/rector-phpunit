<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Enum;

final class PHPUnitClassName
{
    public const string TEST_CASE = 'PHPUnit\Framework\TestCase';

    /**
     * @api might be used in public
     */
    public const string TEST_CASE_LEGACY = 'PHPUnit_Framework_TestCase';

    public const string ASSERT = 'PHPUnit\Framework\Assert';

    public const string INVOCATION_ORDER = 'PHPUnit\Framework\MockObject\Rule\InvocationOrder';

    public const string TEST_LISTENER = 'PHPUnit\Framework\TestListener';

    /**
     * @var string[]
     */
    public const array TEST_CLASSES = [self::TEST_CASE, self::TEST_CASE_LEGACY];
}
