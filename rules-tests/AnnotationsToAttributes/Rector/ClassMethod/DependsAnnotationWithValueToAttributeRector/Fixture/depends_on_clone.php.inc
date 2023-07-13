<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

class DependsOnClone extends \PHPUnit\Framework\TestCase
{
    public function testOne() {}
    /**
     * @depends clone testOne
     */
    public function testTwo(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

class DependsOnClone extends \PHPUnit\Framework\TestCase
{
    public function testOne() {}
    #[\PHPUnit\Framework\Attributes\DependsUsingDeepClone('testOne')]
    public function testTwo(): void
    {
    }
}

?>
