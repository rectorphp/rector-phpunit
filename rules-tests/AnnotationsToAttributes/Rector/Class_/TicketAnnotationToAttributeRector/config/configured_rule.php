<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\AnnotationsToAttributes\Rector\Class_\TicketAnnotationToAttributeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(TicketAnnotationToAttributeRector::class);
};
