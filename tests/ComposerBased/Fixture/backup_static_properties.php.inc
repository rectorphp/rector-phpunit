<?php

use PHPUnit\Framework\TestCase;

class BackupStaticPropertiesTest extends TestCase
{
    /**
     * @backupStaticProperties enabled
     */
    public function testSomething()
    {
    }

    /**
     * @excludeGlobalVariableFromBackup someGlobalVariable
     */
    public function testSomethingElse()
    {
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
    }

    #[\PHPUnit\Framework\Attributes\ExcludeGlobalVariableFromBackup('someGlobalVariable')]
    public function testSomethingElse()
    {
    }
}

?>
