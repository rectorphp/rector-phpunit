<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\TestWithAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFixtureWithTestAttribute extends TestCase
{
    /**
     * @testWith ["foo"]
     *           ["bar"]
     */
    #[\PHPUnit\Framework\Attributes\Test]
    public function shouldDoSomething(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\TestWithAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFixtureWithTestAttribute extends TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
    #[\PHPUnit\Framework\Attributes\TestWith(['foo'])]
    #[\PHPUnit\Framework\Attributes\TestWith(['bar'])]
    public function shouldDoSomething(): void
    {
    }
}

?>
