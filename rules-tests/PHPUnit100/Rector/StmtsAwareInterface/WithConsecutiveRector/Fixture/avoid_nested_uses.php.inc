<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AvoidNestedUses extends TestCase
{
    public function test()
    {
        $value = 1000;

        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, $value],
                [2, function ($nested) {
                    $nestedReturn = 1000;
                    return $nestedReturn;
                }],
            );
    }

    private function some()
    {

    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AvoidNestedUses extends TestCase
{
    public function test()
    {
        $value = 1000;
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function (...$parameters) use ($matcher, $value) {
            match ($matcher->numberOfInvocations()) {
                1 => self::assertEquals([1, $value], $parameters),
                2 => self::assertEquals([2, function ($nested) {
                    $nestedReturn = 1000;
                    return $nestedReturn;
                }], $parameters),
            };
        });
    }

    private function some()
    {

    }
}

?>
