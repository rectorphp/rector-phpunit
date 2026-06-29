<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

class KeepDeepCallsBeforeAssertHelper extends TestCase
{
    public function testSomething(): void
    {
        // a deep, non-asserting call chain visited before the assert helper;
        // it must not exhaust the nested-call budget and hide the assertion below
        $this->prepare();

        $this->checkResult(true);
    }

    private function prepare(): void
    {
        $this->stepTwo();
    }

    private function stepTwo(): void
    {
        $this->stepThree();
    }

    private function stepThree(): void
    {
        $this->stepFour();
    }

    private function stepFour(): void
    {
        $this->stepFive();
    }

    private function stepFive(): void
    {
        // no assertion here
    }

    private function checkResult(bool $bool): void
    {
        self::assertTrue($bool);
    }
}
