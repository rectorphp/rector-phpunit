<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

class CalculatorTestCase extends TestCase {}
class Calculator {}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture\Calculator::class)]
class CalculatorTestCase extends TestCase {}
class Calculator {}

?>
