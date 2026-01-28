<?php

namespace Rector\PHPUnit\Tests\Issues\DoubleAnnotation\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture\SomeClass;

final class SomeTest extends TestCase
{
    /**
     * @covers \SomeClass::method
     * @dataProvider generatorInput
     */
    public function testSomething(mixed $expected)
    {
        $this->assertSame($expected, 'actual');
    }

    public function generatorInput()
    {
    }
}

-----
<?php

namespace Rector\PHPUnit\Tests\Issues\DoubleAnnotation\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture\SomeClass;

#[\PHPUnit\Framework\Attributes\CoversMethod(\SomeClass::class, 'method')]
final class SomeTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('generatorInput')]
    public function testSomething(mixed $expected)
    {
        $this->assertSame($expected, 'actual');
    }

    public function generatorInput()
    {
    }
}

