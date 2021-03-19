<?php

declare(strict_types=1);

namespace Rector\Tests\PHPUnit\TestClassResolver;

use Iterator;
use Rector\Core\HttpKernel\RectorKernel;
use Rector\PHPUnit\TestClassResolver\TestClassResolver;
use Rector\Tests\PHPUnit\TestClassResolver\Source\SeeSomeClass;
use Rector\Tests\PHPUnit\TestClassResolver\Source\SeeSomeClassTest;
use Symplify\PackageBuilder\Testing\AbstractKernelTestCase;

final class TestClassResolverTest extends AbstractKernelTestCase
{
    /**
     * @var TestClassResolver
     */
    private $testClassResolver;

    protected function setUp(): void
    {
        $this->bootKernelWithConfigs(RectorKernel::class, [
            __DIR__ . '/../../config/config.php'
        ]);
        $this->testClassResolver = $this->getService(TestClassResolver::class);
    }

    /**
     * @dataProvider provideData()
     */
    public function test(string $rectorClass, string $expectedTestClass): void
    {
        $testClass = $this->testClassResolver->resolveFromClassName($rectorClass);
        $this->assertSame($expectedTestClass, $testClass);
    }

    /**
     * @return Iterator<mixed>
     */
    public function provideData(): Iterator
    {
        yield [SeeSomeClass::class, SeeSomeClassTest::class];
    }
}
