<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector\Source\AnyBook;

class SkipSoleType extends TestCase
{
    private MockObject $anyBook;
}
