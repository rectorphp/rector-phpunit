<?php

namespace Symfony\Bundle\FrameworkBundle\Test;

use PHPUnit\Framework\TestCase;

abstract class KernelTestCase extends TestCase
{
    protected function setUp(): void
    {
        // asserts on purpose, to prove the file is never parsed
        $this->assertTrue(true);
    }
}
