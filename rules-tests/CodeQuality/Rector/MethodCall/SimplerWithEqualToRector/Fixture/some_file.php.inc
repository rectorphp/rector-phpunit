<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithEqualToRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFile extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->exactly(2))
            ->method('add')
            ->with($this->callback(function ($type): bool {
                $this->assertSame(TextType::class, $type);

                return true;
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithEqualToRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFile extends TestCase
{
    public function test()
    {
        $builder = $this->getMockBuilder('AnyType')->getMock();

        $builder->expects($this->exactly(2))
            ->method('add')
            ->with($this->equalTo(TextType::class));
    }
}

?>
