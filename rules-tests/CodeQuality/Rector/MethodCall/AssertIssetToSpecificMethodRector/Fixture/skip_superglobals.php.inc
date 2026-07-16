<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipSuperglobals extends TestCase
{
    public function test(): void
    {
        self::assertFalse(isset($GLOBALS['userconfig']));
        self::assertFalse(isset($_SERVER['userconfig']));
        self::assertFalse(isset($_GET['userconfig']));
        self::assertFalse(isset($_POST['userconfig']));
        self::assertFalse(isset($_FILES['userconfig']));
        self::assertFalse(isset($_COOKIE['userconfig']));
        self::assertFalse(isset($_SESSION['userconfig']));
        self::assertFalse(isset($_REQUEST['userconfig']));
        self::assertFalse(isset($_ENV['userconfig']));
    }
}
