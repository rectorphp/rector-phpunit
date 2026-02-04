<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturnMap([1, 2]);
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->expects($this->exactly(2))->method('some')->willReturnMap([1, 2]);
    }
}

?>
