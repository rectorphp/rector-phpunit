<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\CreateMockToAnonymousClassRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\ClassMethod\CreateMockToAnonymousClassRector\Source\ToBeFixturedClass;

final class MockedMoreMethods extends TestCase
{
    public function test()
    {
        $someMockObject = $this->createMock(ToBeFixturedClass::class);

        $someMockObject->method('firstMethod')
            ->willReturn(100);

        $someMockObject->method('secondMethod')
            ->willReturn([200]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\CreateMockToAnonymousClassRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\ClassMethod\CreateMockToAnonymousClassRector\Source\ToBeFixturedClass;

final class MockedMoreMethods extends TestCase
{
    public function test()
    {
        $someMockObject = new class extends ToBeFixturedClass
        {
            public function firstMethod()
            {
                return 100;
            }
            public function secondMethod()
            {
                return [200];
            }
        };
    }
}

?>
