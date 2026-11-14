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

    /**
     * PHPUnit 13 moved the interface out of the Builder namespace
     */
    public const string INVOCATION_MOCKER_INTERFACE = 'PHPUnit\Framework\MockObject\InvocationMocker';

    public const string INVOCATION_STUBBER = 'PHPUnit\Framework\MockObject\InvocationStubber';

    public const string TEST_LISTENER = 'PHPUnit\Framework\TestListener';

    public const string MOCK_OBJECT = 'PHPUnit\Framework\MockObject\MockObject';

    public const string STUB = 'PHPUnit\Framework\MockObject\Stub';

    public const string SYMFONY_TYPE_TEST_CASE = 'Symfony\Component\Form\Test\TypeTestCase';

    public const string SYMFONY_KERNEL_TEST_CASE = 'Symfony\Bundle\FrameworkBundle\Test\KernelTestCase';

    public const string SYMFONY_WEB_TEST_CASE = 'Symfony\Bundle\FrameworkBundle\Test\WebTestCase';

    public const string TWIG_INTEGRATION_TEST_CASE = 'Twig\Test\IntegrationTestCase';

    /**
     * @var string[]
     */
    public const array TEST_CLASSES = [self::TEST_CASE, self::TEST_CASE_LEGACY];

    /**
     * Framework base test classes, their methods do not count as test assertions and their files are huge to parse
     *
     * @var string[]
     */
    public const array FRAMEWORK_TEST_CASES = [
        self::TEST_CASE,
        self::ASSERT,
        self::SYMFONY_KERNEL_TEST_CASE,
        self::SYMFONY_WEB_TEST_CASE,
        self::SYMFONY_TYPE_TEST_CASE,
    ];
}
