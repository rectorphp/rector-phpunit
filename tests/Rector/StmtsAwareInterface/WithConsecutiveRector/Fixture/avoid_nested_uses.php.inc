<?php

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

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

namespace Rector\PHPUnit\Tests\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AvoidNestedUses extends TestCase
{
    public function test()
    {
        $value = 1000;
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')->willReturnCallback(function () use ($matcher, $value) {
            return match ($matcher->numberOfInvocations()) {
                1 => [1, $value],
                2 => [2, function ($nested) {
                    $nestedReturn = 1000;
                    return $nestedReturn;
                }],
            };
        });
    }

    private function some()
    {

    }
}

?>
