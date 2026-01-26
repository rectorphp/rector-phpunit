<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source;

final class AnotherClass
{
    public function __construct($one, $two, $three, private $someMock)
    {

    }

    public function getSomeMock()
    {
        return $this->someMock;
    }
}
