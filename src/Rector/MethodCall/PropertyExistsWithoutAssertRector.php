<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\FuncCall;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\New_;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Name;
use PhpParser\Node\Name\FullyQualified;
use PhpParser\Node\Scalar\String_;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\IdentifierManipulator;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\MethodCall\PropertyExistsWithoutAssertRector\PropertyExistsWithoutAssertRectorTest
 */
final class PropertyExistsWithoutAssertRector extends AbstractRector
{
    /**
     * @var array<string, string>
     */
    private const RENAME_METHODS_WITH_OBJECT_MAP = [
        'assertObjectHasAttribute' => 'assertTrue',
        'assertObjectNotHasAttribute' => 'assertFalse',
    ];

    /**
     * @var array<string, string>
     */
    private const RENAME_METHODS_WITH_CLASS_MAP = [
        'assertClassHasAttribute' => 'assertTrue',
        'assertClassNotHasAttribute' => 'assertFalse',
    ];

    public function __construct(
        private readonly IdentifierManipulator $identifierManipulator,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Turns PHPUnit TestCase assertObjectHasAttribute into `property_exists` comparisons',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
$this->assertClassHasAttribute("property", "Class");
$this->assertClassNotHasAttribute("property", "Class");
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
$this->assertFalse(property_exists(new Class, "property"));
$this->assertTrue(property_exists(new Class, "property"));
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [MethodCall::class, StaticCall::class];
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($node, [
            'assertClassHasAttribute',
            'assertClassNotHasAttribute',
            'assertObjectNotHasAttribute',
            'assertObjectHasAttribute',
        ])) {
            return null;
        }

        $arguments = array_column($node->args, 'value');
        if (
            $arguments[0] instanceof String_ ||
            $arguments[0] instanceof Variable ||
            $arguments[0] instanceof ArrayDimFetch ||
            $arguments[0] instanceof PropertyFetch
        ) {
            $secondArg = $arguments[0];
        } else {
            return null;
        }

        if ($arguments[1] instanceof Variable) {
            $firstArg = new Variable($arguments[1]->name);
            $map = self::RENAME_METHODS_WITH_OBJECT_MAP;
        } elseif ($arguments[1] instanceof String_) {
            $firstArg = new New_(new FullyQualified($arguments[1]->value));
            $map = self::RENAME_METHODS_WITH_CLASS_MAP;
        } elseif ($arguments[1] instanceof PropertyFetch || $arguments[1] instanceof ArrayDimFetch) {
            $firstArg = $arguments[1];
            $map = self::RENAME_METHODS_WITH_OBJECT_MAP;
        } else {
            return null;
        }

        unset($node->args[0]);
        unset($node->args[1]);

        $propertyExistsFuncCall = new FuncCall(new Name('property_exists'), [
            new Arg($firstArg),
            new Arg($secondArg),
        ]);

        $newArgs = $this->nodeFactory->createArgs([$propertyExistsFuncCall]);

        $node->args = $this->appendArgs($newArgs, $node->getArgs());
        $this->identifierManipulator->renameNodeWithMap($node, $map);

        return $node;
    }
}
