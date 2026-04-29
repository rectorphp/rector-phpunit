<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use stdClass;

final class SkipUsedByWillReturn extends TestCase
{
    public function test()
    {
        $classMetadata = $this->createMock(stdClass::class);
        $this->configureMainDocMetadata($classMetadata);

        $documentManager = $this->createMock(ObjectManager::class);
        $documentManager->expects($this->atLeastOnce())
            ->method('getClassMetadata')
            ->willReturn($classMetadata);
    }

    private function configureMainDocMetadata(MockObject $classMetadata)
    {
        $classMetadata->expects($this->atLeastOnce())
            ->method('getName')
            ->willReturn('SomeClass');
    }
}
