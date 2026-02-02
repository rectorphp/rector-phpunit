<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertThatToDirectAssertRector\Fixture;

final class ThatAssertTrue extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertThat('value', $this->isTrue());

        $this->assertThat('name', $this->isType('string'));
        $this->assertThat('age', $this->isString());
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertThatToDirectAssertRector\Fixture;

final class ThatAssertTrue extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue('value');

        $this->assertIsString('name');
        $this->assertIsString('age');
    }
}

?>
