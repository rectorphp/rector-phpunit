<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

trait SomeTestTrait
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

trait SomeTestTrait
{
    #[\PHPUnit\Framework\Attributes\DataProvider('someMethod')]
    public function test(): void
    {
    }
}

?>
