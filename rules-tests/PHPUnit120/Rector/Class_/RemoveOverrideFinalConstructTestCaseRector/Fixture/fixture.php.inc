<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\RemoveOverrideFinalConstructTestCaseRector;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
    public function __construct()
    {
        parent::__construct(static::class);
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\RemoveOverrideFinalConstructTestCaseRector;

use PHPUnit\Framework\TestCase;

final class Fixture extends TestCase
{
}
?>
