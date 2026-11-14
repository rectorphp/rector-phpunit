<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class SkipExpectUserDeprecationMessageTest extends \PHPUnit\Framework\TestCase
{
    public function testExpectUserDeprecationMessage()
    {
        $this->expectUserDeprecationMessage('Since foo 1.0: Bar is deprecated.');

        @trigger_error('Since foo 1.0: Bar is deprecated.', E_USER_DEPRECATED);
    }

    public function testExpectUserDeprecationMessageMatches()
    {
        $this->expectUserDeprecationMessageMatches('#^Since foo 1\.0#');

        @trigger_error('Since foo 1.0: Bar is deprecated.', E_USER_DEPRECATED);
    }
}
