<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithConsecutiveInnerAssert extends TestCase
{
    public function test()
    {
        $this->someMock->expects(self::exactly(2))->method('publish')->withConsecutive(
            [
                $this->equalTo('one'),
                $this->equalTo('two')
            ],
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithConsecutiveInnerAssert extends TestCase
{
    public function test()
    {
        $matcher = self::exactly(2);

        $this->someMock->expects($matcher)->method('publish')->willReturnCallback(function (...$parameters) use ($matcher) {
            if ($matcher->getInvocationCount() === 1) {
                $this->assertEquals('once', $parameters[0]);
                $this->assertEquals('two', $parameters[1]);
            }
        });
    }
}

?>
