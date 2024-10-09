<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturn extends TestCase
{
    public function test()
    {
        $this->userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1],
            )
            ->willReturn(5);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturn extends TestCase
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
                    return 5;
                },
            );
    }
}

?>
