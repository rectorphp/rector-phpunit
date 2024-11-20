<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FooTest extends TestCase
{
    /**
     * @dataProvider \Tests\Foo\ExternalProvider::barProvider
     **/
    public function testBar()
    {
        self::assertTrue(true);
    }
}

final class ExternalProvider
{
    public static function barProvider()
    {}
}

?>
