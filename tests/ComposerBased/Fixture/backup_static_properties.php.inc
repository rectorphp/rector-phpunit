<?php

use PHPUnit\Framework\TestCase;

class BackupStaticPropertiesTest extends TestCase
{
    /**
     * @backupStaticProperties enabled
     */
    public function testSomething()
    {
        $this->assertTrue(true);
    }

    /**
     * @excludeGlobalVariableFromBackup someGlobalVariable
     */
    public function testSomethingElse()
    {
        $this->assertTrue(true);
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class BackupStaticPropertiesTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\BackupStaticProperties(true)]
    public function testSomething()
    {
        $this->assertTrue(true);
    }

    #[\PHPUnit\Framework\Attributes\ExcludeGlobalVariableFromBackup('someGlobalVariable')]
    public function testSomethingElse()
    {
        $this->assertTrue(true);
    }
}

?>
