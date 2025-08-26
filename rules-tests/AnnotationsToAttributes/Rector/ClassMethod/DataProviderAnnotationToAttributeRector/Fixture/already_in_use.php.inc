<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class AlreadyInUse extends TestCase
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

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class AlreadyInUse extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('@dataProvider')]
    public function test(): void
    {
    }
}

?>
