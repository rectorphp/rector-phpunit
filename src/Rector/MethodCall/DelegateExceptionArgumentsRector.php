<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFactory\AssertCallFactory;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\DelegateExceptionArgumentsRectorTest
 */
final class DelegateExceptionArgumentsRector extends AbstractRector
{
    /**
     * @var array<string, string>
     */
    private const OLD_TO_NEW_METHOD = [
        'setExpectedException' => 'expectExceptionMessage',
        'setExpectedExceptionRegExp' => 'expectExceptionMessageRegExp',
    ];

    /**
     * @var AssertCallFactory
     */
    private $assertCallFactory;

    /**
     * @var TestsNodeAnalyzer
     */
    private $testsNodeAnalyzer;

    public function __construct(AssertCallFactory $assertCallFactory, TestsNodeAnalyzer $testsNodeAnalyzer)
    {
        $this->assertCallFactory = $assertCallFactory;
        $this->testsNodeAnalyzer = $testsNodeAnalyzer;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Takes `setExpectedException()` 2nd and next arguments to own methods in PHPUnit.',
            [
                new CodeSample(
                    '$this->setExpectedException(Exception::class, "Message", "CODE");',
                    <<<'CODE_SAMPLE'
$this->setExpectedException(Exception::class);
$this->expectExceptionMessage('Message');
$this->expectExceptionCode('CODE');
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
        $oldMethodNames = array_keys(self::OLD_TO_NEW_METHOD);
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($node, $oldMethodNames)) {
            return null;
        }

        if (isset($node->args[1])) {
            /** @var Identifier $identifierNode */
            $identifierNode = $node->name;
            $oldMethodName = $identifierNode->name;

            $call = $this->assertCallFactory->createCallWithName($node, self::OLD_TO_NEW_METHOD[$oldMethodName]);
            $call->args[] = $node->args[1];
            $this->addNodeAfterNode($call, $node);

            unset($node->args[1]);

            // add exception code method call
            if (isset($node->args[2])) {
                $call = $this->assertCallFactory->createCallWithName($node, 'expectExceptionCode');
                $call->args[] = $node->args[2];
                $this->addNodeAfterNode($call, $node);

                unset($node->args[2]);
            }
        }

        $node->name = new Identifier('expectException');

        return $node;
    }
}
