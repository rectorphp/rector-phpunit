<?php

/**
 * 2 classes here on purpose to test that the rector will not add a @see annotation to the first class, because it already has one.
 */
namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddSeeTestAnnotationRector\Fixture;

/**
 * @see SkipExistingShortSeeTest
 */
class SkipExistingShortSee
{
}

class SkipExistingShortSeeTest extends \PHPUnit\Framework\TestCase
{
}
