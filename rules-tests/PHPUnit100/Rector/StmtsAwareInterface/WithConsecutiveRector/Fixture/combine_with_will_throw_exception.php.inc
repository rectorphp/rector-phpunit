<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use RuntimeException;

final class CombineWithWillThrowException extends TestCase
{
    public function test()
    {
        $this->userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1],
            )
            ->willThrowException(new RuntimeException());
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use RuntimeException;

final class CombineWithWillThrowException extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(
                function (...$parameters) use ($matcher) {
                    if ($matcher->numberOfInvocations() === 1) {
                        $this->assertSame(1, $parameters[0]);
                    }
                    throw new RuntimeException();
                },
            );
    }
}

?>
