<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveStandaloneCreateMockRector\Fixture;

final class HandleNestedCall extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
        $this->createMock('someClass')
            ->method('some')
            ->willReturn(100);
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveStandaloneCreateMockRector\Fixture;

final class HandleNestedCall extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
    }
}

?>
