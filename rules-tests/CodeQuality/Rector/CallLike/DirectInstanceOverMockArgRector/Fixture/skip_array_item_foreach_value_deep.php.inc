<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArrayItemForeachValueDeep extends TestCase
{
    public function testThat()
    {
        $regex = '/(?P<version>\d+\.\d+\.\d+)/';
        $contents = 'VERSION: 1.0.0';
        $operations = [];

        if (preg_match_all($regex, $contents, $matches, PREG_OFFSET_CAPTURE | PREG_SET_ORDER) > 0) {
            foreach ($matches as ['version' => [$fullVersion, $offset]]) {
                $operations[] = [$fullVersion, $offset];
            }
        }
    }
}
