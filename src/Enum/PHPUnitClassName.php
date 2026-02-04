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

    public const string INVOCATION_MOCKER = 'PHPUnit\Framework\MockObject\Builder\InvocationMocker';

    public const string INVOCATION_STUBBER = 'PHPUnit\Framework\MockObject\InvocationStubber';

    public const string TEST_LISTENER = 'PHPUnit\Framework\TestListener';

    public const string MOCK_OBJECT = 'PHPUnit\Framework\MockObject\MockObject';

    public const string STUB = 'PHPUnit\Framework\MockObject\Stub';

    public const string SYMFONY_CONSTRAINT_VALIDATOR_TEST_CASE = 'Symfony\Component\Validator\Test\ConstraintValidatorTestCase';

    public const string SYMFONY_TYPE_TEST_CASE = 'Symfony\Component\Form\Test\TypeTestCase';

    /**
     * @var string[]
     */
    public const array TEST_CLASSES = [self::TEST_CASE, self::TEST_CASE_LEGACY];
}
