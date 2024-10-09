<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MergeWithReturnCallback extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->method('prepare')
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

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MergeWithReturnCallback extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)->method('prepare')
            ->willReturnCallback(function ($parameters) use ($matcher) {
                if ($matcher->numberOfInvocations() === 1) {
                    $this->assertSame(1, $parameters[0]);
                    $this->assertSame(2, $parameters[1]);
                }
                if ($matcher->numberOfInvocations() === 2) {
                    $this->assertSame(3, $parameters[0]);
                    $this->assertSame(4, $parameters[1]);
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
