<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    /**
     * @dataProvider someMethod()
     */
    public function test(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('someMethod')]
    public function test(): void
    {
    }
}

?>
