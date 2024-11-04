<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeClass;

final class SkipDirectUseWithoutAssignInSetup extends TestCase
{
    private array $data = ['some setup data'];

    protected function setUp(): void
    {
        new SomeClass($this->data);
    }
}