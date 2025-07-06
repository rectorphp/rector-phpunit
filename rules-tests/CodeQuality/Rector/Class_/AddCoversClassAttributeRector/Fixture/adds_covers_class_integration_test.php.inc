<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

class UserRepositoryIntegrationTest extends TestCase {}
class UserRepository {}

?>
-----
<?php

namespace Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(\Utils\Rector\Tests\Rector\AddCoversClassAttributeRector\Fixture\UserRepository::class)]
class UserRepositoryIntegrationTest extends TestCase {}
class UserRepository {}

?>
