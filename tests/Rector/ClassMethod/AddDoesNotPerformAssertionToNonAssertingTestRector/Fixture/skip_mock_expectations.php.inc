<?php

declare(strict_types=1);

namespace AppTest\Client\Adapter;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

interface CacheInterface {}
interface AdapterInterface {}

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

final class CacheAdapter implements AdapterInterface
{
    public static function create(AdapterInterface $adapter, CacheInterface $listCache, CacheInterface $getCache): self
    {
        return new self($adapter, $listCache, $getCache);
    }
    
    private function __construct(
        private readonly AdapterInterface $adapter,
        private readonly CacheInterface $listCache,
        private readonly CacheInterface $getCache,
    ) {
    }
}    

namespace Rector\Tests\PHPUnit\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

final class CachedAdapterTest extends TestCase
{
    /** @var CacheInterface&MockObject */
    private MockObject $listCache;

    /** @var CacheInterface&MockObject */
    private MockObject $getCache;

    /** @var AdapterInterface&MockObject */
    private MockObject $wrappedAdapter;

    /** @var CachedAdapter */
    private CachedAdapter $cachedAdapter;

    protected function setUp(): void
    {
        $this->listCache      = $this->createMock(CacheInterface::class);
        $this->getCache       = $this->createMock(CacheInterface::class);
        $this->wrappedAdapter = $this->createMock(AdapterInterface::class);
        $this->cachedAdapter  = CachedAdapter::create($this->wrappedAdapter, $this->listCache, $this->getCache);
    }

    public function testDeleteRequestsCallTheAdapterThenClearTheListCacheAndRemoveFromGetCache(): void
    {
        $endpoint = 'test';

        $this->getCache
            ->expects(self::never())
            ->method('has');

        $this->wrappedAdapter
            ->expects(self::once())
            ->method('delete')
            ->with($endpoint);

        $this->listCache
            ->expects(self::once())
            ->method('clear');

        $this->getCache
            ->expects(self::once())
            ->method('unset')
            ->with($endpoint);

        $this->cachedAdapter->delete($endpoint);
    }
}

?>
-----
