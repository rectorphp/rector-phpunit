<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ExcludeWillReturnCallback extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            )
            ->willReturnCallback(function () use ($matcher) {
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
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ExcludeWillReturnCallback extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            )
            ->willReturnCallback(function () use ($matcher) {
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
