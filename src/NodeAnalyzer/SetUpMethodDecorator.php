<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Node\Identifier;
use PhpParser\Node\Stmt\ClassMethod;
use Rector\Core\PhpParser\AstResolver;
use Rector\Core\ValueObject\MethodName;
use Rector\Testing\PHPUnit\StaticPHPUnitEnvironment;

/**
 * Decorate setUp() and tearDown() with "void" when local TestClass class uses them
 */
final class SetUpMethodDecorator
{
    public function __construct(
        private readonly AstResolver $astResolver
    ) {
    }

    public function decorate(ClassMethod $classMethod): void
    {
        // skip test run
        if (StaticPHPUnitEnvironment::isPHPUnitRun()) {
            return;
        }

        $setUpClassMethod = $this->astResolver->resolveClassMethod('PHPUnit\Framework\TestCase', MethodName::SET_UP);
        if (! $setUpClassMethod instanceof ClassMethod) {
            return;
        }

        if ($setUpClassMethod->returnType instanceof Identifier) {
            $classMethod->returnType = new Identifier($setUpClassMethod->returnType->toString());
            return;
        }

        $classMethod->returnType = null;
    }
}
