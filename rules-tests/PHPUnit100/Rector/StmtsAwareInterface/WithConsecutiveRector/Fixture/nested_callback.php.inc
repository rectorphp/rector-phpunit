<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class NestedCallback extends TestCase
{
    public function test()
    {
        $this->someMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [
                    $this->equalTo(50),
                    $this->callback(fn ($item): bool => $item === 5),
                    $this->callback(fn ($item): bool => 5 === $item),
                    $this->callback(fn ($item): bool => ! empty($item)),
                    $this->callback(fn ($item): bool => empty($item))
                ]
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class NestedCallback extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);
        $this->someMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(
                function (...$parameters) use ($matcher) {
                    if ($matcher->numberOfInvocations() === 1) {
                        $this->assertEquals(50, $parameters[0]);
                        $this->assertSame(5, $parameters[1]);
                        $this->assertSame(5, $parameters[2]);
                    }
                }
            );
    }
}

?>
