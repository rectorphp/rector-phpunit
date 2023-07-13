<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SkipMissingTestAnnotation extends \PHPUnit\Framework\TestCase
{
    /**
     *
     */
    public function onePlusOneShouldBeTwo()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
