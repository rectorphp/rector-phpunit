<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Identifier;
use PhpParser\Node\Param;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ParamTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\PhpDocParser\Ast\Type\TypeNode;
use PHPStan\Type\Type;
use PHPStan\Type\UnionType;
use PHPUnit\Framework\TestCase;
use Rector\Core\Contract\Rector\ConfigurableRectorInterface;
use Rector\Core\Exception\ShouldNotHappenException;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPStanStaticTypeMapper\Enum\TypeKind;
use Rector\PHPUnit\NodeAnalyzer\ParamAndArgFromArrayResolver;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFactory\DataProviderClassMethodFactory;
use Rector\PHPUnit\ValueObject\ArrayArgumentToDataProvider;
use Rector\PHPUnit\ValueObject\DataProviderClassMethodRecipe;
use Rector\PHPUnit\ValueObject\ParamAndArg;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\ConfiguredCodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use Webmozart\Assert\Assert;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\ArrayArgumentToDataProviderRector\ArrayArgumentToDataProviderRectorTest
 *
 * @see why → https://blog.martinhujer.cz/how-to-use-data-providers-in-phpunit/
 */
final class ArrayArgumentToDataProviderRector extends AbstractRector implements ConfigurableRectorInterface
{
    /**
     * @api
     * @var string
     */
    public const ARRAY_ARGUMENTS_TO_DATA_PROVIDERS = 'array_arguments_to_data_providers';

    /**
     * @var ArrayArgumentToDataProvider[]
     */
    private array $arrayArgumentsToDataProviders = [];

    /**
     * @var DataProviderClassMethodRecipe[]
     */
    private array $dataProviderClassMethodRecipes = [];

    public function __construct(
        private readonly DataProviderClassMethodFactory $dataProviderClassMethodFactory,
        private readonly ParamAndArgFromArrayResolver $paramAndArgFromArrayResolver,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Move array argument from tests into data provider [configurable]', [
            new ConfiguredCodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
    public function test()
    {
        $this->doTestMultiple([1, 2, 3]);
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

class SomeServiceTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(int $number)
    {
        $this->doTestSingle($number);
    }

    public function provideData(): \Iterator
    {
        yield [1];
        yield [2];
        yield [3];
    }
}
CODE_SAMPLE

                ,
                [
                    self::ARRAY_ARGUMENTS_TO_DATA_PROVIDERS => [
                        new ArrayArgumentToDataProvider(
                            TestCase::class,
                            'doTestMultiple',
                            'doTestSingle',
                            'number'
                        ),
                    ],
                ]
            ),
        ]);
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $this->dataProviderClassMethodRecipes = [];

        $classMethod = null;
        $this->traverseNodesWithCallable($node->getMethods(), function (Node $node) use (&$classMethod) {
            if ($node instanceof ClassMethod) {
                $classMethod = $node;
                return null;
            }

            if (! $node instanceof MethodCall) {
                return null;
            }

            foreach ($this->arrayArgumentsToDataProviders as $arrayArgumentToDataProvider) {
                $this->refactorMethodCallWithConfiguration($node, $arrayArgumentToDataProvider, $classMethod);
            }

            return null;
        });

        if ($this->dataProviderClassMethodRecipes === []) {
            return null;
        }

        $dataProviderClassMethods = $this->createDataProviderClassMethodsFromRecipes();

        $node->stmts = array_merge($node->stmts, $dataProviderClassMethods);

        return $node;
    }

    /**
     * @param mixed[] $configuration
     */
    public function configure(array $configuration): void
    {
        $arrayArgumentsToDataProviders = $configuration[self::ARRAY_ARGUMENTS_TO_DATA_PROVIDERS] ?? $configuration;

        Assert::isArray($arrayArgumentsToDataProviders);
        Assert::allIsAOf($arrayArgumentsToDataProviders, ArrayArgumentToDataProvider::class);

        $this->arrayArgumentsToDataProviders = $arrayArgumentsToDataProviders;
    }

    private function refactorMethodCallWithConfiguration(
        MethodCall $methodCall,
        ArrayArgumentToDataProvider $arrayArgumentToDataProvider,
        ?ClassMethod $classMethod
    ): void {
        if (! $classMethod instanceof ClassMethod) {
            return;
        }

        if (! $this->isMethodCallMatch($methodCall, $arrayArgumentToDataProvider)) {
            return;
        }

        if ($methodCall->isFirstClassCallable()) {
            return;
        }

        if (count($methodCall->getArgs()) !== 1) {
            throw new ShouldNotHappenException();
        }

        // resolve value types
        $firstArgumentValue = $methodCall->getArgs()[0]
->value;
        if (! $firstArgumentValue instanceof Array_) {
            // nothing we can do
            return;
        }

        // rename method to new one handling non-array input
        $methodCall->name = new Identifier($arrayArgumentToDataProvider->getNewMethod());

        $dataProviderMethodName = $this->createDataProviderMethodName($classMethod);
        $this->dataProviderClassMethodRecipes[] = new DataProviderClassMethodRecipe(
            $dataProviderMethodName,
            $methodCall->getArgs()
        );

        $methodCall->args = [];

        $paramAndArgs = $this->paramAndArgFromArrayResolver->resolve(
            $firstArgumentValue,
            $arrayArgumentToDataProvider->getVariableName()
        );

        foreach ($paramAndArgs as $paramAndArg) {
            $methodCall->args[] = new Arg($paramAndArg->getVariable());
        }

        $this->refactorTestClassMethodParams($classMethod, $paramAndArgs);

        // add data provider annotation
        $phpDocTagNode = $this->createDataProviderTagNode($dataProviderMethodName);

        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $phpDocInfo->addPhpDocTagNode($phpDocTagNode);
        $phpDocInfo->makeMultiLined();
    }

    /**
     * @return ClassMethod[]
     */
    private function createDataProviderClassMethodsFromRecipes(): array
    {
        $dataProviderClassMethods = [];

        foreach ($this->dataProviderClassMethodRecipes as $dataProviderClassMethodRecipe) {
            $dataProviderClassMethods[] = $this->dataProviderClassMethodFactory->createFromRecipe(
                $dataProviderClassMethodRecipe
            );
        }

        return $dataProviderClassMethods;
    }

    private function isMethodCallMatch(
        MethodCall $methodCall,
        ArrayArgumentToDataProvider $arrayArgumentToDataProvider
    ): bool {
        if (! $this->isObjectType($methodCall->var, $arrayArgumentToDataProvider->getObjectType())) {
            return false;
        }

        return $this->isName($methodCall->name, $arrayArgumentToDataProvider->getOldMethod());
    }

    private function createDataProviderMethodName(ClassMethod $classMethod): string
    {
        $classMethodName = $this->getName($classMethod);
        return 'provideDataFor' . ucfirst($classMethodName);
    }

    /**
     * @param ParamAndArg[] $paramAndArgs
     */
    private function refactorTestClassMethodParams(ClassMethod $classMethod, array $paramAndArgs): void
    {
        $classMethod->params = $this->createParams($paramAndArgs);

        $phpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);

        foreach ($paramAndArgs as $paramAndArg) {
            $staticType = $paramAndArg->getType();

            if (! $staticType instanceof UnionType) {
                continue;
            }

            /** @var string $paramName */
            $paramName = $this->getName($paramAndArg->getVariable());

            /** @var TypeNode $staticTypeNode */
            $staticTypeNode = $this->staticTypeMapper->mapPHPStanTypeToPHPStanPhpDocTypeNode($staticType);

            $paramTagValueNode = $this->createParamTagNode($paramName, $staticTypeNode);
            $phpDocInfo->addTagValueNode($paramTagValueNode);
        }
    }

    private function createDataProviderTagNode(string $dataProviderMethodName): PhpDocTagNode
    {
        return new PhpDocTagNode('@dataProvider', new GenericTagValueNode($dataProviderMethodName . '()'));
    }

    /**
     * @param ParamAndArg[] $paramAndArgs
     * @return Param[]
     */
    private function createParams(array $paramAndArgs): array
    {
        $params = [];
        foreach ($paramAndArgs as $paramAndArg) {
            $param = new Param($paramAndArg->getVariable());
            $this->setTypeIfNotNull($paramAndArg, $param);

            $params[] = $param;
        }

        return $params;
    }

    private function createParamTagNode(string $name, TypeNode $typeNode): ParamTagValueNode
    {
        return new ParamTagValueNode($typeNode, false, '$' . $name, '');
    }

    private function setTypeIfNotNull(ParamAndArg $paramAndArg, Param $param): void
    {
        $staticType = $paramAndArg->getType();
        if (! $staticType instanceof Type) {
            return;
        }

        if ($staticType instanceof UnionType) {
            return;
        }

        $phpNodeType = $this->staticTypeMapper->mapPHPStanTypeToPhpParserNode($staticType, TypeKind::PARAM);
        if ($phpNodeType === null) {
            return;
        }

        $param->type = $phpNodeType;
    }
}
