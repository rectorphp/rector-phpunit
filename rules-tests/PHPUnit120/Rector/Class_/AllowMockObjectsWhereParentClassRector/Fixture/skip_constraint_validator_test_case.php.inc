<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Validator\Test\ConstraintValidatorTestCase;

final class SkipConstraintValidatorTestCase extends ConstraintValidatorTestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}
