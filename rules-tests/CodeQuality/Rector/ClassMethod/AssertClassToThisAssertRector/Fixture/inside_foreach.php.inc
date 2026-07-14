<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class InsideForeach extends TestCase
{
    public function testOriginalKeyOrderingForFullAssociativeArray(): void
    {
        $entityMock = $this->createMock(SomeEntity::class);
        $entityMock->method('getId')
            ->willReturn(1);
        $entities = [$entityMock];

        $parameters = [
            ['id' => 1, 'foo' => 'bar'],
        ];

        $helper = new SomeHelper($parameters);
        $orderedEntities = $helper->orderByOriginalKey($entities);

        $this->assertSame([0], array_keys($orderedEntities));

        foreach ($parameters as $key => $contact) {
            Assert::assertEquals($orderedEntities[$key]->getId(), $entities[$key]->getId());
        }
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class InsideForeach extends TestCase
{
    public function testOriginalKeyOrderingForFullAssociativeArray(): void
    {
        $entityMock = $this->createMock(SomeEntity::class);
        $entityMock->method('getId')
            ->willReturn(1);
        $entities = [$entityMock];

        $parameters = [
            ['id' => 1, 'foo' => 'bar'],
        ];

        $helper = new SomeHelper($parameters);
        $orderedEntities = $helper->orderByOriginalKey($entities);

        $this->assertSame([0], array_keys($orderedEntities));

        foreach ($parameters as $key => $contact) {
            $this->assertEquals($orderedEntities[$key]->getId(), $entities[$key]->getId());
        }
    }
}

?>
