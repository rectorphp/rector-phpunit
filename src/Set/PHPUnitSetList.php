<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Set;

/**
 * @api
 */
final class PHPUnitSetList
{
    public const string PHPUNIT_MOCK_TO_STUB = __DIR__ . '/../../config/sets/phpunit-mock-to-stub.php';

    public const string PHPUNIT_CODE_QUALITY = __DIR__ . '/../../config/sets/phpunit-code-quality.php';

    public const string PHPUNIT_NARROW_ASSERTS = __DIR__ . '/../../config/sets/phpunit-narrow-asserts.php';

    public const string ANNOTATIONS_TO_ATTRIBUTES = __DIR__ . '/../../config/sets/annotations-to-attributes.php';

    public const string COMPOSER_BASED = __DIR__ . '/../../config/sets/composer-based.php';
}
