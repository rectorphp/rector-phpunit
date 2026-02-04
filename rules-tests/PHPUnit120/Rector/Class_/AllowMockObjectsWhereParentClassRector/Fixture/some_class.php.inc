<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Validator\Test\ConstraintValidatorTestCase;

final class SomeClass extends ConstraintValidatorTestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Validator\Test\ConstraintValidatorTestCase;

#[\PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations]
final class SomeClass extends ConstraintValidatorTestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}

?>
