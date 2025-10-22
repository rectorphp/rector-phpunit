<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Source\SomeObjectWithPublicProperties;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someObject = new SomeObjectWithPublicProperties();

        $this->assertSame([
            'name' => 'John',
            'surname' => 'Doe',
        ], (array) $someObject);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\AssertArrayCastedObjectToAssertSameRector\Source\SomeObjectWithPublicProperties;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someObject = new SomeObjectWithPublicProperties();
        $this->assertSame('John', $someObject->name);
        $this->assertSame('Doe', $someObject->surname);
    }
}

?>
