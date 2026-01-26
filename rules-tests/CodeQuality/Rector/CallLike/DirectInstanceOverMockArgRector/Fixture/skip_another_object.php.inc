<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Source\AnotherObject;
use Symfony\Component\HttpFoundation\Request;

final class SkipAnotherObject extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(
            $this->createMock(AnotherObject::class),
        );
    }
}
