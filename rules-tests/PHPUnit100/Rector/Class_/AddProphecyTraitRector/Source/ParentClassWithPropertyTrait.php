<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\AddProphecyTraitRector\Source;

use PHPUnit\Framework\TestCase;

abstract class ParentClassWithPropertyTrait extends TestCase
{
    use \Prophecy\PhpUnit\ProphecyTrait;
}
