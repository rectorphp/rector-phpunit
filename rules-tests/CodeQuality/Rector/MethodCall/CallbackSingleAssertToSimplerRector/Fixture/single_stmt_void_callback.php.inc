<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\CallbackSingleAssertToSimplerRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SingleStmtVoidCallback extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->once())
            ->method('queueWebhooksByType')
            ->with($this->callback(function ($type): void {
                $this->assertSame($type, 'some_value');
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\CallbackSingleAssertToSimplerRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SingleStmtVoidCallback extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->once())
            ->method('queueWebhooksByType')
            ->with($this->equalTo('some_value'));
    }
}

?>
