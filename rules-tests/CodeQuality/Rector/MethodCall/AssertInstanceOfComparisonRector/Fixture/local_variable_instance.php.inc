<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

final class LocalVariableInstanceTest extends \PHPUnit\Framework\TestCase
{
    public function testAddForm(): void
    {
        $form = ['formAlias' => 'testform'];
        $result = $event->addForm($form);

        $this->assertTrue($result instanceof ConfigBuilderEvent);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

final class LocalVariableInstanceTest extends \PHPUnit\Framework\TestCase
{
    public function testAddForm(): void
    {
        $form = ['formAlias' => 'testform'];
        $result = $event->addForm($form);

        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\ConfigBuilderEvent::class, $result);
    }
}

?>
