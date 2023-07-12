<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillReturnTrue extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('Symfony\Component\Translation\TranslatorInterface');
        $translator->expects($this->any())
            ->method('trans')
            ->will($this->returnValue(true));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillReturnTrue extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('Symfony\Component\Translation\TranslatorInterface');
        $translator->expects($this->any())
            ->method('trans')
            ->willReturn(true);
    }
}

?>
