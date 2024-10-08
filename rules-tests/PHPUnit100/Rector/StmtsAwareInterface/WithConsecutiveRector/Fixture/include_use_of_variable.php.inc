<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

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
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IncludeUseOfVariable extends TestCase
{
    public function test()
    {
        $value = 1000;
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(
                function (...$parameters) use ($matcher, $value) {
                    if ($matcher->numberOfInvocations() === 1) {
                        $this->assertSame(1, $parameters[0]);
                        $this->assertSame($value, $parameters[1]);
                    }
                },
            );
    }
}

?>
