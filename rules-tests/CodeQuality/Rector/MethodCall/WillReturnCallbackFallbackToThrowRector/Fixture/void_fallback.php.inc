<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToThrowRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VoidFallback extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(1);

        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($matcher)
            ->method('run')
            ->willReturnCallback(function () use ($matcher) {
                if ($matcher->numberOfInvocations() === 1) {
                    return 'first';
                }
            });
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToThrowRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VoidFallback extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(1);

        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($matcher)
            ->method('run')
            ->willReturnCallback(function () use ($matcher) {
                if ($matcher->numberOfInvocations() === 1) {
                    return 'first';
                }
                throw new \PHPUnit\Framework\Exception(sprintf('Method should not be called for the %dth time', $matcher->numberOfInvocations()));
            });
    }
}

?>
