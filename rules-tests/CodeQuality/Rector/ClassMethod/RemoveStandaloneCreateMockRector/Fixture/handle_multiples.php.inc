<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveStandaloneCreateMockRector\Fixture;

final class HandleMultiples extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
        $this->createMock('someClass');
        $this->createMock('someClass');
        $this->createMock('someClass');
        $this->createMock('someClass');
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveStandaloneCreateMockRector\Fixture;

final class HandleMultiples extends \PHPUnit\Framework\TestCase
{
    public function testSomething(): void
    {
    }
}

?>
