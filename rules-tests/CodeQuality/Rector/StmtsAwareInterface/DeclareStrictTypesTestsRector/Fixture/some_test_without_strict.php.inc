<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\StmtsAwareInterface\DeclareStrictTypesTestsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestWithoutStrict extends TestCase
{
    public function test()
    {
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\StmtsAwareInterface\DeclareStrictTypesTestsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestWithoutStrict extends TestCase
{
    public function test()
    {
    }
}
