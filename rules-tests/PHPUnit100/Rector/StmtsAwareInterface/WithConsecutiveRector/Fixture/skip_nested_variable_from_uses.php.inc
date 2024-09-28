<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNestedVariableFromUses extends TestCase
{
    public function test()
    {
        $this->someMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                $this->callback(fn ($item): bool => $item === 5),
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNestedVariableFromUses extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);
        $this->someMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(
                function (...$parameters) use ($matcher) {
                    match ($matcher->numberOfInvocations()) {
                        1 => self::assertEquals($this->callback(fn ($item): bool => $item === 5), $parameters),
                    };
                },
            );
    }
}

?>
