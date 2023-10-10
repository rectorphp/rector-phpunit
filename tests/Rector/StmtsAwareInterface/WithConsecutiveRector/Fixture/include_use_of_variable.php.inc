<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IncludeUseOfVariable extends TestCase
{
    public function test()
    {
        $value = 1000;

        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, $value],
                [3, 4],
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IncludeUseOfVariable extends TestCase
{
    public function test()
    {
        $value = 1000;
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function () use ($matcher, $value) {
            return match ($matcher->getInvocationCount()) {
                1 => [1, $value],
                2 => [3, 4],
            };
        });
    }
}

?>
