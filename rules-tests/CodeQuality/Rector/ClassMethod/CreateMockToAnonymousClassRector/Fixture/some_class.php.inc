<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Source\ToBeFixturedClass;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someMockObject = $this->createMock(ToBeFixturedClass::class);

        $someMockObject->method('someMethod')
            ->willReturn(100);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\CreateMockToAnonymousClassRector\Source\ToBeFixturedClass;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someMockObject = new class extends ToBeFixturedClass
        {
            public function someMethod()
            {
                return 100;
            }
        };
    }
}

?>
