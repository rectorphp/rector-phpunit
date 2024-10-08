<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnReference extends TestCase
{
    public function test()
    {
        $value = 42;
        $this->userServiceMock->expects(self::exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1],
            )
            ->willReturnReference($value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnReference extends TestCase
{
    public function test()
    {
        $value = 42;
        $matcher = self::exactly(2);
        $this->userServiceMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(
                function &(...$parameters) use ($matcher, $value) {
                    if ($matcher->numberOfInvocations() === 1) {
                        $this->assertSame(1, $parameters[0]);
                    }
                    return $value;
                },
            );
    }
}

?>
