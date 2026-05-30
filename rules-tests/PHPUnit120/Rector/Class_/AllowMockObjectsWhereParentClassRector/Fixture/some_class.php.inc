<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Form\Test\TypeTestCase;

final class SomeClass extends TypeTestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector\Fixture;

use Symfony\Component\Form\Test\TypeTestCase;

#[\PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations]
final class SomeClass extends TypeTestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;
}

?>
