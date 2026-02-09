<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddKeysExistsAssertForKeyUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeArrayValueAssert extends TestCase
{
    public function test(): void
    {
        $data = $this->getData();
        $this->assertSame(123, $data['key']);
    }

    private function getData(): array
    {
        if (mt_rand(0, 1)) {
            return ['key' => 123];
        }

        return [];
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AddKeysExistsAssertForKeyUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeArrayValueAssert extends TestCase
{
    public function test(): void
    {
        $data = $this->getData();
        $this->assertArrayHasKey('key', $data, 'Existing keys are: ' . implode(', ', array_keys($data)));
        $this->assertSame(123, $data['key']);
    }

    private function getData(): array
    {
        if (mt_rand(0, 1)) {
            return ['key' => 123];
        }

        return [];
    }
}

?>
