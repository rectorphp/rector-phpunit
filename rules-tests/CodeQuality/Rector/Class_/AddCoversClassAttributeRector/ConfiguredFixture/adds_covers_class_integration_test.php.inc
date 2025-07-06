<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture;

use PHPUnit\Framework\TestCase;

class UserRepositoryIntegrationTest extends TestCase {}
class UserRepository {}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\ConfiguredFixture\UserRepository::class)]
class UserRepositoryIntegrationTest extends TestCase {}
class UserRepository {}

?>
