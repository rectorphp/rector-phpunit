<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnSelfThis extends TestCase
{
    public function test()
    {
        $userServiceMock = $this->createMock(\Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture\CombineWithWillReturnSelfThis::class);
        $userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            )
            ->willReturnSelf();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnSelfThis extends TestCase
{
    public function test()
    {
        $userServiceMock = $this->createMock(\Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture\CombineWithWillReturnSelfThis::class);
        $matcher = self::exactly(2);
        $userServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function ($parameters) use ($matcher, $userServiceMock) : void {
            match ($matcher->numberOfInvocations()) {
                1 => self::assertEquals([1, 2], $parameters),
                2 => self::assertEquals([3, 4], $parameters),
            };
            return $userServiceMock;
        });
    }
}

?>
