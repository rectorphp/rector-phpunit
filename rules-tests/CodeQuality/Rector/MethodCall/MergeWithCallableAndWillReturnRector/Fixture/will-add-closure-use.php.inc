<?php

namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

final class DemoFile extends PHPUnit\Framework\TestCase
{
    public function test_it(): void
    {
        $initialStatements = [
            new FakeNode(),
            new FakeNode(),
        ];

        $this->fileParserMock
            ->expects($this->once())
            ->method('parse')
            ->with($this->callback(
                function (SplFileInfo $fileInfo): bool {
                    $this->assertSame('/path/to/file', $fileInfo->getRealPath());

                    return true;
                },
            ))
            ->willReturn([$initialStatements, []])
        ;
    }

}
?>
-----
<?php

namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

final class DemoFile extends PHPUnit\Framework\TestCase
{
    public function test_it(): void
    {
        $initialStatements = [
            new FakeNode(),
            new FakeNode(),
        ];

        $this->fileParserMock
            ->expects($this->once())
            ->method('parse')
            ->willReturnCallback(function (SplFileInfo $fileInfo) use ($initialStatements): array {
                $this->assertSame('/path/to/file', $fileInfo->getRealPath());

                return [$initialStatements, []];
            })
        ;
    }

}
?>
