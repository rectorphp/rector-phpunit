<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnOnConsecutiveCalls extends TestCase
{
    public function test()
    {
        $this->userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            )
            ->willReturnOnConsecutiveCalls(5, 6);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnOnConsecutiveCalls extends TestCase
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
            switch ($matcher->numberOfInvocations()) {
                case 1:
                    return 5;
                case 2:
                    return 6;
            }
        });
    }
}

?>
