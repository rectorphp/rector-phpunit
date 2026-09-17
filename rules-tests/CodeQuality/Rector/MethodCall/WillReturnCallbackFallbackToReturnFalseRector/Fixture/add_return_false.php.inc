<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AddReturnFalse extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);

        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->expects($matcher)->method('checkContext')->willReturnCallback(function (...$parameters) use ($matcher) {
            if (1 === $matcher->numberOfInvocations()) {
                $this->assertSame(['email.stats', 'emails'], $parameters[0]);

                return true;
            }
            if (2 === $matcher->numberOfInvocations()) {
                $this->assertSame('emails', $parameters[0]);

                return false;
            }
        });
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AddReturnFalse extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);

        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->expects($matcher)->method('checkContext')->willReturnCallback(function (...$parameters) use ($matcher) {
            if (1 === $matcher->numberOfInvocations()) {
                $this->assertSame(['email.stats', 'emails'], $parameters[0]);

                return true;
            }
            if (2 === $matcher->numberOfInvocations()) {
                $this->assertSame('emails', $parameters[0]);

                return false;
            }
            return false;
        });
    }
}

?>
