<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Foreach_\SimplifyForeachInstanceOfRector\Fixture;

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

final class SkipMessageTest extends WebTestCase
{
    public function testExpectedClassAsArrayElement(array $actualProviders, array $expectedProviders)
    {
        foreach ($actualProviders as $key => $provider) {
            $this->assertInstanceOf(
                $expectedProviders[$key],
                $provider,
                sprintf('"%s" instanceof "%s"', $provider::class, $expectedProviders[$key])
            );
        }
    }
}
