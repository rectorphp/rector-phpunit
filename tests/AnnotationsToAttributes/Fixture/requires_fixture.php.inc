<?php

use PHPUnit\Framework\TestCase;

/**
 * @requires PHP > 8.4
 * @requires PHPUnit >= 10
 * @requires OS Windows
 * @requires OSFAMILY Darwin
 * @requires function someFunction
 * @requires function \some\className::someMethod
 * @requires extension mysqli
 * @requires extension mysqli >= 8.3.0
 * @requires setting date.timezone Europe/Berlin
 */
class BarController extends TestCase
{
    /**
     * @requires PHP > 8.4
     * @requires PHPUnit >= 10
     * @requires OS Windows
     * @requires OSFAMILY Darwin
     * @requires function someFunction
     * @requires function \some\className::someMethod
     * @requires extension mysqli
     * @requires extension mysqli >= 8.3.0
     * @requires setting date.timezone Europe/Berlin
     */
    public function testWithRequires()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\RequiresPhp('> 8.4')]
#[\PHPUnit\Framework\Attributes\RequiresPhpunit('>= 10')]
#[\PHPUnit\Framework\Attributes\RequiresOperatingSystem('Windows')]
#[\PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily('Darwin')]
#[\PHPUnit\Framework\Attributes\RequiresFunction('someFunction')]
#[\PHPUnit\Framework\Attributes\RequiresMethod(\some\className::class, 'someMethod')]
#[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli')]
#[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli', '>= 8.3.0')]
#[\PHPUnit\Framework\Attributes\RequiresSetting('date.timezone', 'Europe/Berlin')]
class BarController extends TestCase
{
    #[\PHPUnit\Framework\Attributes\RequiresPhp('> 8.4')]
    #[\PHPUnit\Framework\Attributes\RequiresPhpunit('>= 10')]
    #[\PHPUnit\Framework\Attributes\RequiresOperatingSystem('Windows')]
    #[\PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily('Darwin')]
    #[\PHPUnit\Framework\Attributes\RequiresFunction('someFunction')]
    #[\PHPUnit\Framework\Attributes\RequiresMethod(\some\className::class, 'someMethod')]
    #[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli')]
    #[\PHPUnit\Framework\Attributes\RequiresPhpExtension('mysqli', '>= 8.3.0')]
    #[\PHPUnit\Framework\Attributes\RequiresSetting('date.timezone', 'Europe/Berlin')]
    public function testWithRequires()
    {
    }
}

?>
