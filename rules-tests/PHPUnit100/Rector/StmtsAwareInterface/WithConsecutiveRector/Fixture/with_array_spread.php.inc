<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithArraySpread extends TestCase
{
    public function test($items)
    {
        $this->personServiceMock->method('prepare')
            ->expects($this->exactly(count($items)))
            ->withConsecutive(
                ...$items
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithArraySpread extends TestCase
{
    public function test($items)
    {
        $matcher = $this->exactly(count($items));
        $this->personServiceMock->method('prepare')
            ->expects($matcher)
            ->willReturnCallback(function (...$parameters) use ($matcher, $items): void {
                self::assertSame($items[$matcher->getInvocationCount() - 1], $parameters);
            });
    }
}

?>
