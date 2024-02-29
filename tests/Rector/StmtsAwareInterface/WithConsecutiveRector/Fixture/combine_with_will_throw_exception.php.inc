<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use RuntimeException;

final class CombineWithWillThrowException extends TestCase
{
    public function test()
    {
        $this->userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            )
            ->willThrowException(new RuntimeException());
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use RuntimeException;

final class CombineWithWillThrowException extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function ($parameters) use ($matcher) {
            switch ($matcher->numberOfInvocations()) {
                case 1:
                    self::assertEquals([1, 2], $parameters);
                    break;
                case 2:
                    self::assertEquals([3, 4], $parameters);
                    break;
            }
            throw new RuntimeException();
        });
    }
}

?>
