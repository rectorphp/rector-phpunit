<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

final class SkipNonTestClassSpreadNamedArg
{
    public function run($request)
    {
        return new SomeData(
            ...$request->updateData(),
            user: (string) $request->user()->getKey(),
        );
    }
}
