<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Source\Table;


final class SomeFileTest extends TestCase
{
    public function test()
    {
        $tableMock = $this->createMock(Table::class);

        $tableMock
            ->expects(self::once())
            ->method('isLocked')
            ->willReturn(true);

        $tableMock
            ->expects(self::once())
            ->method('setLocked')
            ->with(false)
            ->willReturn($tableMock);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Source\Table;


final class SomeFileTest extends TestCase
{
    public function test()
    {
        $table = new \Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Source\Table();

        $table->setLocked(true);
    }
}

?>
