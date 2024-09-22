<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

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

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithOnConsecutiveWithoutExcepts extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);
        $this->userServiceMock->method('prepare')->willReturnCallback(function ($parameters) use ($matcher) {
            match ($matcher->numberOfInvocations()) {
                1 => self::assertEquals([1, 2], $parameters),
                2 => self::assertEquals([3, 4], $parameters),
            };
            return match ($matcher->numberOfInvocations()) {
                1 => 5,
                2 => 6,
            };
        });
    }
}

?>
