<?php

declare(strict_types=1);

use PhpCsFixer\Fixer\ReturnNotation\ReturnAssignmentFixer;
use Symplify\EasyCodingStandard\Config\ECSConfig as ECSConfigAlias;
use Symplify\EasyCodingStandard\ValueObject\Set\SetList;

return static function (ECSConfigAlias $ecsConfig): void {
    $ecsConfig->sets([SetList::SYMPLIFY, SetList::COMMON, SetList::CLEAN_CODE, SetList::PSR_12]);

    $ecsConfig->paths([
        __DIR__ . '/src',
        __DIR__ . '/tests',
        __DIR__ . '/config',
        __DIR__ . '/ecs.php',
        __DIR__ . '/rector.php',
    ]);

    $ecsConfig->skip([
        '*/Source/*', '*/Fixture/*',

        // breaks annotated code - removed on symplify dev-main
        ReturnAssignmentFixer::class,
    ]);

    $ecsConfig->lineEnding("\n");
};
