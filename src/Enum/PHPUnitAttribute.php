<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Enum;

final class PHPUnitAttribute
{
    public const string REQUIRES_PHP = 'PHPUnit\Framework\Attributes\RequiresPhp';

    public const string REQUIRES_PHPUNIT = 'PHPUnit\Framework\Attributes\RequiresPhpunit';

    public const string REQUIRES_OS = 'PHPUnit\Framework\Attributes\RequiresOperatingSystem';

    public const string REQUIRES_OS_FAMILY = 'PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily';

    public const string REQUIRES_METHOD = 'PHPUnit\Framework\Attributes\RequiresMethod';

    public const string REQUIRES_FUNCTION = 'PHPUnit\Framework\Attributes\RequiresFunction';

    public const string REQUIRES_PHP_EXTENSION = 'PHPUnit\Framework\Attributes\RequiresPhpExtension';

    public const string REQUIRES_SETTING = 'PHPUnit\Framework\Attributes\RequiresSetting';

    public const string TEST = 'PHPUnit\Framework\Attributes\Test';

    /**
     * @see https://github.com/sebastianbergmann/phpunit/commit/24c208d6a340c3071f28a9b5cce02b9377adfd43
     */
    public const string ALLOW_MOCK_OBJECTS_WITHOUT_EXPECTATIONS = 'PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations';
}
