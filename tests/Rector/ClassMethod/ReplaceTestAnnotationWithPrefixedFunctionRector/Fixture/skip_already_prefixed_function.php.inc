<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\ReplaceTestAnnotationWithPrefixedFunctionRector\Fixture;

class SkipAlreadyPrefixedFunction extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     */
    public function testOnePlusOneShouldBeTwo()
    {
        $this->assertSame(2, 1+1);
    }
}

?>