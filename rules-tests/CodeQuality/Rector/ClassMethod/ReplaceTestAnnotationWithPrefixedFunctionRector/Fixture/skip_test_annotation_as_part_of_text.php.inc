<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SkipTestAnnotationAsPartOfText extends \PHPUnit\Framework\TestCase
{
    /**
     * there is some comment with something@test
     * @test-different-annotation
     */
    public function onePlusOneShouldBeTwo()
    {
        $this->assertSame(2, 1+1);
    }
}

?>
