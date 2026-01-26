<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PhpParser\Node\Arg;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Foreach_;
use PHPStan\Reflection\ReflectionProvider;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PhpParser\Node\Value\ValueResolver;

final readonly class AssignedMocksCollector
{
    public function __construct(
        private ReflectionProvider $reflectionProvider,
        private ValueResolver $valueResolver,
        private NodeNameResolver $nodeNameResolver,
        private DoctrineEntityDocumentAnalyser $doctrineEntityDocumentAnalyser,
    ) {
    }

    /**
     * @return array<string, string>
     */
    public function collect(ClassMethod|Foreach_ $stmtsAware): array
    {
        if ($stmtsAware->stmts === null) {
            return [];
        }

        $mockedVariablesToTypes = [];

        foreach ($stmtsAware->stmts as $stmt) {
            // find assign mock
            if (! $stmt instanceof Expression) {
                continue;
            }

            if (! $stmt->expr instanceof Assign) {
                continue;
            }

            $assign = $stmt->expr;

            $firstArg = $this->matchCreateMockArgAssignedToVariable($assign);
            if (! $firstArg instanceof Arg) {
                continue;
            }

            $mockedClass = $this->valueResolver->getValue($firstArg->value);
            if (! is_string($mockedClass)) {
                continue;
            }

            if (! $this->reflectionProvider->hasClass($mockedClass)) {
                continue;
            }

            $mockClassReflection = $this->reflectionProvider->getClass($mockedClass);
            // these cannot be instantiated
            if ($mockClassReflection->isAbstract()) {
                continue;
            }

            if ($mockClassReflection->isInterface()) {
                continue;
            }

            $mockedVariableName = $this->nodeNameResolver->getName($assign->var);
            $mockedVariablesToTypes[$mockedVariableName] = $mockedClass;
        }

        return $mockedVariablesToTypes;
    }

    /**
     * @return array<string, string>
     */
    public function collectEntityClasses(ClassMethod $classMethod): array
    {
        $variableNamesToClassNames = $this->collect($classMethod);

        $variableNamesToEntityClasses = [];

        foreach ($variableNamesToClassNames as $variableName => $className) {
            if (! $this->doctrineEntityDocumentAnalyser->isEntityClass($className)) {
                continue;
            }

            $variableNamesToEntityClasses[$variableName] = $className;
        }

        return $variableNamesToEntityClasses;
    }

    public function matchCreateMockArgAssignedToVariable(Assign $assign): ?Arg
    {
        if (! $assign->var instanceof Variable) {
            return null;
        }

        if (! $assign->expr instanceof MethodCall) {
            return null;
        }

        $methodCall = $assign->expr;
        if (! $this->nodeNameResolver->isName($methodCall->name, 'createMock')) {
            return null;
        }

        if ($methodCall->isFirstClassCallable()) {
            return null;
        }

        return $methodCall->getArgs()[0];
    }
}
