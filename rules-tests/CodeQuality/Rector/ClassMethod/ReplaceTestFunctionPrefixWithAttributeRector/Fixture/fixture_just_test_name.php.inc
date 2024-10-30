<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test_()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
    public function test_()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
