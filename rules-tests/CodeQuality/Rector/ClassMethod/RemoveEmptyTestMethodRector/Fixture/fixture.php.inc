<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveEmptyTestMethodRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    /**
     * testGetTranslatedModelField method
     *
     * @return void
     */
    public function testGetTranslatedModelField()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\RemoveEmptyTestMethodRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
}

?>
