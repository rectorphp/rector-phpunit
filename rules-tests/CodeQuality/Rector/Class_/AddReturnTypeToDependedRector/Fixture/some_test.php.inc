<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    public function test()
    {
        return new \stdClass();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    public function test(): \stdClass
    {
        return new \stdClass();
    }
}

?>
