<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SecondParamOnlyTest extends TestCase
{
    public function test(): void
    {
        $builder = self::createMock(\stdClass::class);

        $this->getEventListener(new \DateTime('now'), $builder);
    }

    private function getEventListener(\DateTime $dateTime, \PHPUnit\Framework\MockObject\MockObject $builder): void
    {
        $builder->expects($this->once())
            ->method('add');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SecondParamOnlyTest extends TestCase
{
    public function test(): void
    {
        $builder = self::createMock(\stdClass::class);

        $this->getEventListener(new \DateTime('now'), $builder);
    }

    /**
     * @param \stdClass&\PHPUnit\Framework\MockObject\MockObject $builder
     */
    private function getEventListener(\DateTime $dateTime, \PHPUnit\Framework\MockObject\MockObject $builder): void
    {
        $builder->expects($this->once())
            ->method('add');
    }
}

?>
