<?php
declare(strict_types=1);

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Source;

trait ExistingTrait
{
    public function __construct()
    {
    }

    public function foo(): void
    {
    }

    public function bar(): void
    {
    }
}
