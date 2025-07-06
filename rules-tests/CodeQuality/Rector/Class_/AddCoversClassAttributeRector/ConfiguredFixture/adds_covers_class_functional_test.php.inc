<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture;

use PHPUnit\Framework\TestCase;

class SomeServiceFunctionalTest extends TestCase {}
class SomeService {}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture\SomeService::class)]
class SomeServiceFunctionalTest extends TestCase {}
class SomeService {}

?>
