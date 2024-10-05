<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithOnConsecutiveWithoutExcepts extends TestCase
{
    public function test()
    {
        $this->userServiceMock->method('prepare')
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

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithOnConsecutiveWithoutExcepts extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);
        $this->userServiceMock->expects($matcher)->method('prepare')->willReturnCallback(function (...$parameters) use ($matcher) {
            if ($matcher->numberOfInvocations() === 1) {
                $this->assertSame([1, 2], $parameters);
                return 5;
            }
            if ($matcher->numberOfInvocations() === 2) {
                $this->assertSame([3, 4], $parameters);
                return 6;
            }
        });
    }
}

?>
