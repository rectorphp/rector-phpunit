<?php

use rocket\tests\lib\WebTestCase;

/**
 * @no-named-arguments
 */
class WithoutNamespaceTest extends \PHPUnit\Framework\TestCase
{
    public function testAuth(): void
    {
        [$headers, $body] = $this->httpGetRaw('/tinymce/auth');

        self::assertArrayHasKey(0, $headers);
        self::assertStringContainsString('200', $headers[0], 'response contained a proper http status-code');
    }
}

?>
-----
<?php

declare(strict_types=1);

use rocket\tests\lib\WebTestCase;

/**
 * @no-named-arguments
 */
class WithoutNamespaceTest extends \PHPUnit\Framework\TestCase
{
    public function testAuth(): void
    {
        [$headers, $body] = $this->httpGetRaw('/tinymce/auth');

        self::assertArrayHasKey(0, $headers);
        self::assertStringContainsString('200', $headers[0], 'response contained a proper http status-code');
    }
}

?>