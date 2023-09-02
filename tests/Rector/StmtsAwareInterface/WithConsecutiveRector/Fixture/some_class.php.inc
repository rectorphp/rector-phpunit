<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);
        $this->personServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function () use ($matcher) {
            return match ($matcher->numberOfInvocations()) {
                1 => [1, 2],
                2 => [3, 4],
            };
        });
    }
}

?>
