<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillOnConsecutiveCalls extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('Symfony\Component\Translation\TranslatorInterface');
        $translator->expects($this->any())
            ->will($this->onConsecutiveCalls([1, 2, 3]));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillOnConsecutiveCalls extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('Symfony\Component\Translation\TranslatorInterface');
        $translator->expects($this->any())
            ->willReturnOnConsecutiveCalls([1, 2, 3]);
    }
}

?>
