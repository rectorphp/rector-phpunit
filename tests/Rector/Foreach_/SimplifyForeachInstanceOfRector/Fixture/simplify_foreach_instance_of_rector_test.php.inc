<?php

namespace Rector\PHPUnit\Tests\Rector\Foreach_\SimplifyForeachInstanceOfRector\Fixture;

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

final class SimplifyForeachInstanceOfRectorTest extends WebTestCase
{
    public function testExpectedClassAsArrayElement()
    {
        $actualProviders = [
        	'provider_key' => new \StdClass(),
        ];
        $expectedProviders = [
        	'provider_key' => \StdClass::class,
        ];
        foreach ($actualProviders as $key => $provider) {
            $this->assertInstanceOf($expectedProviders[$key], $provider, sprintf('"%s" instanceof "%s"', $provider::class, $expectedProviders[$key]));
        }
    }
}
