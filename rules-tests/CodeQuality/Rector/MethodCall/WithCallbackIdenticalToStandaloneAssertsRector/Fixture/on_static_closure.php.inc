<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class OnStaticClosure extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->expects($this->once())
            ->method('someMethod')
            ->with($this->callback(static function (array $args): bool {
               return count($args) === 2 && $args[0] === 'correct';
            }));
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class OnStaticClosure extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->expects($this->once())
            ->method('someMethod')
            ->with($this->callback(static function (array $args): bool {
                self::assertCount(2, $args);
                self::assertSame('correct', $args[0]);
                return true;
            }));
    }
}

?>
