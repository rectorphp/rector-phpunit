<?php

namespace Twig\Test;

use PHPUnit\Framework\TestCase;

abstract class IntegrationTestCase extends TestCase
{
    /**
     * @param array<string, string> $templates
     * @param array<string> $outputs
     */
    protected function doIntegrationTest(
        string $file,
        string $message,
        string $condition,
        array $templates,
        string $exception,
        array $outputs,
        string $deprecation = ''
    ): void {
    }
}
