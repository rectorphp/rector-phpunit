<?php

declare(strict_types=1);

use Rector\PHPUnit\AnnotationsToAttributes\Rector\Class_\TicketAnnotationToAttributeRector;
use Rector\PHPUnit\Tests\ConfigList;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {

    $rectorConfig->rule(TicketAnnotationToAttributeRector::class);
};
