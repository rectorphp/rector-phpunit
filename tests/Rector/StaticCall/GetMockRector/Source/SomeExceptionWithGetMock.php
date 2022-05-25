<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Rector\StaticCall\GetMockRector\Source;

final class SomeExceptionWithGetMock extends \Exception
{
    public function getMock()
    {
    }
}
