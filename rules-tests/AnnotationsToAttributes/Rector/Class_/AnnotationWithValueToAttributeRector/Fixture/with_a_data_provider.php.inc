<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithADataProvider extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {

    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithADataProvider extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('provideData()')]
    public function test()
    {

    }
}

?>
