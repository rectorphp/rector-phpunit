<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VaribleAssigned extends TestCase
{
    public function test()
    {
        $someValue = rand(0, 1);

        return $someValue;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VaribleAssigned extends TestCase
{
    public function test(): int
    {
        $someValue = rand(0, 1);

        return $someValue;
    }
}

?>
