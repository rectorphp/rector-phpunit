<?php

declare(strict_types=1);

use Symplify\EasyCodingStandard\Config\ECSConfig;
use Symplify\EasyCodingStandard\ValueObject\Set\SetList;

return static function (ECSConfig $ecsConfig): void {
    $ecsConfig->sets([SetList::SYMPLIFY, SetList::COMMON, SetList::CLEAN_CODE, SetList::PSR_12]);

    $ecsConfig->paths([
        __DIR__ . '/src',
        __DIR__ . '/tests',
        __DIR__ . '/config',
        __DIR__ . '/ecs.php',
        __DIR__ . '/rector.php',
    ]);

    $ecsConfig->skip(['*/Source/*', '*/Fixture/*', '*/Expected/*']);

    $ecsConfig->lineEnding("\n");
};
