<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Validator\Test\ConstraintValidatorTestCase;

abstract class IntermediateConstraintValidatorBase extends ConstraintValidatorTestCase
{
}

final class SkipConstraintValidatorTestCaseViaIntermediate extends IntermediateConstraintValidatorBase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}
