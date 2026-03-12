<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewlinedRector\Fixture;

use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class SkipTestMethod extends TestCase
{
    #[Test]
    public function run(): void
    {
        $importer = self::createMock(Importer::class);
        $importer->expects($invokedCount)
            ->method('processFiles')
            ->willReturnCallback(function (array $parameters) use ($invokedCount): array {
                switch ($invokedCount->numberOfInvocations()) {
                    case 1:
                        self::assertSame(range(1, 250), $parameters);

                        return [233, [], []];
                    case 2:
                        self::assertSame(range(251, 500), $parameters);

                        return [15, [], []];

                    default:
                        throw new \OutOfBoundsException('Did not expect this to run thrice.');
                }
            });
    }
}
