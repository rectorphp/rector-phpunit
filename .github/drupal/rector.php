<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector;

// run from Drupal root, see .github/workflows/drupal.yaml
return RectorConfig::configure()
    ->withPaths([getcwd() . '/core/tests', getcwd() . '/core/modules'])
    ->withRules([AddDoesNotPerformAssertionToNonAssertingTestRector::class]);
