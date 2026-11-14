<?php

declare(strict_types=1);

/**
 * Benchmark for AddDoesNotPerformAssertionToNonAssertingTestRector on test classes with deep parent chains.
 *
 * Each test class has parent lifecycle hooks (setUp(), tearDown()) and parent::test*() calls. Resolving these
 * via AstResolver parses and decorates parent files on first use, so every scenario measures one cold pass, as in a real run.
 *
 * Scenarios, all with the same shape (see the constants below):
 * - inherited:       parents have non-asserting hooks, the test classes have none. Every test method changes.
 * - own set up:      like "inherited", but each test class has its own setUp() calling parent::setUp(). The file of
 *                    the test class is already parsed by Rector, it must not be parsed a second time to look at its hooks.
 * - asserting hooks: the top parent of each chain has an asserting hook (setUp(), assertPostConditions() or a
 *                    #[Before] method), so the lifecycle analyzer walks the whole chain and no test method changes.
 *
 * Run on both branches to compare. CPU (user+sys) is the reliable metric; wall is noisy.
 */

use PhpParser\Node\Stmt\Class_;
use Rector\DependencyInjection\LazyContainerFactory;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\PHPUnit\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector;
use Rector\Testing\TestingParser\TestingParser;

require __DIR__ . '/../vendor/autoload.php';

const CHAINS = 10;          // independent base class chains
const DEPTH = 4;            // abstract parents per chain, between TestCase and the test class
const TESTS_PER_CHAIN = 30; // test classes extending the deepest parent of each chain
const TEST_METHODS = 5;     // non-asserting test methods per test class
const FILLER_METHODS = 15;  // extra methods per parent class, to make parsing realistic
const MAX_CPU_SECONDS = 1.0; // fails in CI above this

const SCENARIOS = [
    'inherited' => [
        'own_set_up' => false,
        'asserting_hooks' => false,
    ],
    'own set up' => [
        'own_set_up' => true,
        'asserting_hooks' => false,
    ],
    'asserting hooks' => [
        'own_set_up' => false,
        'asserting_hooks' => true,
    ],
];

$cpuSeconds = static function (): float {
    $usage = getrusage();
    return $usage['ru_utime.tv_sec'] + $usage['ru_utime.tv_usec'] / 1_000_000
        + $usage['ru_stime.tv_sec'] + $usage['ru_stime.tv_usec'] / 1_000_000;
};

$directory = sys_get_temp_dir() . '/rector_phpunit_bench_' . getmypid();
@mkdir($directory);

// make generated classes visible to PHPStan reflection
spl_autoload_register(static function (string $class) use ($directory): void {
    if (! str_starts_with($class, 'Bench\\')) {
        return;
    }

    $filePath = $directory . '/' . substr($class, 6) . '.php';
    if (is_file($filePath)) {
        require_once $filePath;
    }
});

$isFailed = false;
$scenarioIndex = 0;

foreach (SCENARIOS as $scenarioName => $scenario) {
    // own class names per scenario, so no scenario profits from the parsed files of another
    $prefix = 'S' . $scenarioIndex++;

    $writeClass = static function (string $className, string $body) use ($directory): string {
        $filePath = $directory . '/' . $className . '.php';
        file_put_contents($filePath, "<?php\n\nnamespace Bench;\n\n" . $body);
        return $filePath;
    };

    $testFilePaths = [];

    for ($chain = 0; $chain < CHAINS; ++$chain) {
        $parentClassName = '\PHPUnit\Framework\TestCase';

        for ($level = 0; $level < DEPTH; ++$level) {
            $className = sprintf('%sAbstractChain%dLevel%d', $prefix, $chain, $level);

            $methods = "    protected function setUp(): void\n    {\n        parent::setUp();\n        \$this->prepare{$level}();\n    }\n\n";
            $methods .= "    protected function tearDown(): void\n    {\n        \$this->cleanup = null;\n        parent::tearDown();\n    }\n\n";
            $methods .= "    public function testInherited(): void\n    {\n        \$value = {$level};\n    }\n\n";
            $methods .= "    private function prepare{$level}(): void\n    {\n        \$this->ready = true;\n    }\n\n";

            if ($scenario['asserting_hooks'] && $level === 0) {
                // the asserting hook is in the top parent, furthest away from the test classes
                $methods .= match ($chain % 3) {
                    0 => "    protected function assertPostConditions(): void\n    {\n        \$this->assertTrue(\$this->ready);\n    }\n\n",
                    1 => "    #[\PHPUnit\Framework\Attributes\Before]\n    protected function checkReady(): void\n    {\n        \$this->assertNotNull(\$this->cleanup);\n    }\n\n",
                    default => "    protected function assertPreConditions(): void\n    {\n        \$this->assertFalse(\$this->ready);\n    }\n\n",
                };
            }

            for ($filler = 0; $filler < FILLER_METHODS; ++$filler) {
                $methods .= "    protected function helper{$filler}(array \$items): array\n    {\n        return array_map(fn (\$item) => \$item * {$filler}, \$items);\n    }\n\n";
            }

            $writeClass(
                $className,
                "abstract class {$className} extends {$parentClassName}\n{\n    protected \$ready;\n    protected \$cleanup;\n\n{$methods}}\n"
            );

            $parentClassName = $className;
        }

        for ($test = 0; $test < TESTS_PER_CHAIN; ++$test) {
            $className = sprintf('%sChain%dTest%d', $prefix, $chain, $test);

            $methods = '';
            if ($scenario['own_set_up']) {
                $methods .= "    protected function setUp(): void\n    {\n        parent::setUp();\n        \$this->ready = true;\n    }\n\n";
            }

            $methods .= "    public function testInherited(): void\n    {\n        parent::testInherited();\n    }\n\n";
            for ($testMethod = 0; $testMethod < TEST_METHODS; ++$testMethod) {
                $methods .= "    public function testSomething{$testMethod}(): void\n    {\n        \$value = \$this->helper{$testMethod}([1, 2, 3]);\n    }\n\n";
            }

            $testFilePaths[] = $writeClass(
                $className,
                "final class {$className} extends {$parentClassName}\n{\n{$methods}}\n"
            );
        }
    }

    $rectorConfig = (new LazyContainerFactory())->create();
    $rectorConfig->boot();

    /** @var TestingParser $testingParser */
    $testingParser = $rectorConfig->make(TestingParser::class);

    /** @var BetterNodeFinder $betterNodeFinder */
    $betterNodeFinder = $rectorConfig->make(BetterNodeFinder::class);

    $rector = $rectorConfig->make(AddDoesNotPerformAssertionToNonAssertingTestRector::class);

    // parse test files up front, parent files are left for the rule to resolve
    $classes = [];
    foreach ($testFilePaths as $testFilePath) {
        $stmts = $testingParser->parseFileToDecoratedNodes($testFilePath);
        $classes = [...$classes, ...$betterNodeFinder->findInstanceOf($stmts, Class_::class)];
    }

    $wallStart = microtime(true);
    $cpuStart = $cpuSeconds();

    $changedCount = 0;
    foreach ($classes as $class) {
        if ($rector->refactor($class) instanceof Class_) {
            ++$changedCount;
        }
    }

    $cpu = $cpuSeconds() - $cpuStart;
    $wall = microtime(true) - $wallStart;

    printf('%s: test classes: %d, changed: %d%s', $scenarioName, count($classes), $changedCount, PHP_EOL);
    printf('CPU:  %.4f s  (%.3f ms/class)%s', $cpu, $cpu / count($classes) * 1000, PHP_EOL);
    printf('wall: %.4f s%s', $wall, PHP_EOL);

    if ($cpu > MAX_CPU_SECONDS) {
        printf('CPU %.4f s is over the %.1f s limit%s', $cpu, MAX_CPU_SECONDS, PHP_EOL);
        $isFailed = true;
    }

}

array_map('unlink', glob($directory . '/*.php'));
@rmdir($directory);

exit($isFailed ? 1 : 0);
