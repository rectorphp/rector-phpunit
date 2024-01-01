<?php

declare(strict_types=1);

use Rector\Contract\Rector\RectorInterface;
use Rector\Set\Contract\SetListInterface;
use Symplify\EasyCI\Config\EasyCIConfig;

return static function (EasyCIConfig $easyCIConfig): void {
    $easyCIConfig->paths([
        __DIR__ . '/config',
        __DIR__ . '/src',
        __DIR__ . '/rules',
    ]);

    $easyCIConfig->typesToSkip([
        RectorInterface::class,
        SetListInterface::class,
    ]);
};
