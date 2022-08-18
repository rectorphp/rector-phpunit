<?php

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

namespace Rector\Tests\PHPUnit\Rector\Foreach_\SimplifyForeachInstanceOfRector\Fixture;

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

?>
