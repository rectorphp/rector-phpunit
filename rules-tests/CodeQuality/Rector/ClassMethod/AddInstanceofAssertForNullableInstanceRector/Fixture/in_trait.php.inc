<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

trait InTrait
{
    public function test(\Throwable $e)
    {
        $p = $e->getPrevious();
        $p->getMessage();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddInstanceofAssertForNullableInstanceRector\Fixture;

trait InTrait
{
    public function test(\Throwable $e)
    {
        $p = $e->getPrevious();
        $this->assertInstanceOf(\Throwable::class, $p);
        $p->getMessage();
    }
}

?>
