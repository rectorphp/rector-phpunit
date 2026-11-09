<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnOnConsecutiveCallsVariable extends TestCase
{
    public function test()
    {
        $title = new \stdClass();

        $this->manager->expects($this->exactly(2))
            ->method('getFieldDefinitions')
            ->withConsecutive(['first'], ['second'])
            ->willReturnOnConsecutiveCalls(['title' => $title], []);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CombineWithWillReturnOnConsecutiveCallsVariable extends TestCase
{
    public function test()
    {
        $title = new \stdClass();
        $matcher = $this->exactly(2);

        $this->manager->expects($matcher)
            ->method('getFieldDefinitions')->willReturnCallback(function (...$parameters) use ($matcher, $title) {
            if ($matcher->numberOfInvocations() === 1) {
                $this->assertSame('first', $parameters[0]);
                return ['title' => $title];
            }
            if ($matcher->numberOfInvocations() === 2) {
                $this->assertSame('second', $parameters[0]);
                return [];
            }
        });
    }
}

?>
