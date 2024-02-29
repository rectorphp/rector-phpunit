<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AvoidUsingThisVariable extends TestCase
{
    public function test()
    {
        $value = 1000;

        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, $value],
                [3, $this->some(4)],
            );
    }

    private function some()
    {

    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AvoidUsingThisVariable extends TestCase
{
    public function test()
    {
        $value = 1000;
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function ($parameters) use ($matcher, $value) {
            switch ($matcher->numberOfInvocations()) {
                case 1:
                    self::assertEquals([1, $value], $parameters);
                    break;
                case 2:
                    self::assertEquals([3, $this->some(4)], $parameters);
                    break;
            }
        });
    }

    private function some()
    {

    }
}

?>
