<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithConsecutiveInnerAssert extends TestCase
{
    public function test()
    {
        $this->someMock->expects(self::exactly(2))->method('publish')->withConsecutive(
            [
                $this->equalTo('one'),
                $this->equalTo(
                    [
                        'two'
                    ]
                ),
            ],
            [
                $this->equalTo('three'),
                $this->equalTo(
                    [
                        'four',
                    ]
                ),
            ]
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithConsecutiveInnerAssert extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function ($parameters) use ($matcher) {
            match ($matcher->numberOfInvocations()) {
                1 => self::assertEquals([1, 2], $parameters),
                2 => self::assertEquals([3, 4], $parameters),
            };
            return $parameters[0];
        });
    }
}

?>
