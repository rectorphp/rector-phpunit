<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\AddTestsVoidReturnTypeWhereNoReturn;

use Iterator;
use PHPUnit\Framework\Attributes\DataProvider;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AddTestsVoidReturnTypeWhereNoReturnTest extends AbstractRectorTestCase
{
    #[DataProvider('provideData')]
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    public static function provideData(): Iterator
    {
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/add_tests_void_return_type_where_no_return.php';
    }
}
