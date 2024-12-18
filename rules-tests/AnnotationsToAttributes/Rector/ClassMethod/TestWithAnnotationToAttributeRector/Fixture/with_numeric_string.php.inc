<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\TestWithAnnotationToAttributeRector\Fixture;

class WithNumericString extends \PHPUnit\Framework\TestCase
{
    /**
     * @testWith ["2"]
     *           ["benjamin.sisko@ds9.example.com"]
     */
    public function testSomething(string $userId): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\TestWithAnnotationToAttributeRector\Fixture;

class WithNumericString extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\TestWith(['2'])]
    #[\PHPUnit\Framework\Attributes\TestWith(['benjamin.sisko@ds9.example.com'])]
    public function testSomething(string $userId): void
    {
    }
}

?>
