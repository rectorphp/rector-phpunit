<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Expr;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use Rector\Core\Enum\ObjectReference;
use Rector\Core\PhpParser\Node\NodeFactory;
use Rector\Core\ValueObject\MethodName;
use Rector\PhpSpecToPHPUnit\PHPUnitTypeDeclarationDecorator;
use Rector\PHPUnit\NodeManipulator\StmtManipulator;
use Symplify\Astral\ValueObject\NodeBuilder\MethodBuilder;

final class SetUpClassMethodFactory
{
    public function __construct(
        private readonly PHPUnitTypeDeclarationDecorator $phpUnitTypeDeclarationDecorator,
        private readonly StmtManipulator $stmtManipulator,
        private readonly NodeFactory $nodeFactory,
    ) {
    }

    /**
     * @param Stmt[]|Expr[] $stmts
     */
    public function createSetUpMethod(array $stmts): ClassMethod
    {
        $stmts = $this->stmtManipulator->normalizeStmts($stmts);

        $classMethodBuilder = new MethodBuilder(MethodName::SET_UP);
        $classMethodBuilder->makeProtected();

        $classMethodBuilder->addStmt($this->createParentStaticCall());
        $classMethodBuilder->addStmts($stmts);

        $classMethod = $classMethodBuilder->getNode();
        $this->phpUnitTypeDeclarationDecorator->decorate($classMethod);

        return $classMethod;
    }

    public function createParentStaticCall(): Expression
    {
        $parentSetupStaticCall = $this->nodeFactory->createStaticCall(ObjectReference::PARENT(), MethodName::SET_UP);
        return new Expression($parentSetupStaticCall);
    }
}
