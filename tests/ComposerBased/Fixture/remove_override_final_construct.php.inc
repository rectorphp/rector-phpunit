<?php

use PHPUnit\Framework\TestCase;

final class RemoveOverrideFinalConstructTest extends TestCase
{
    public function __construct()
    {
        parent::__construct(static::class);
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

final class RemoveOverrideFinalConstructTest extends TestCase
{
}

?>
