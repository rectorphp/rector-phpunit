<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\ClassLike\RemoveTestSuffixFromAbstractTestClassesRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(RemoveTestSuffixFromAbstractTestClassesRector::class);
};
