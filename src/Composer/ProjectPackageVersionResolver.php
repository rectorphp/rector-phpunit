<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Composer;

use Rector\Composer\InstalledPackageResolver;

/**
 * @internal
 *
 * This service allows to customize rule naming based on current package version,
 * e.g. PHPUnit 9 and PHPUnit 10 have different naming for consecutive method calls.
 */
final readonly class ProjectPackageVersionResolver
{
    public function __construct(
        private InstalledPackageResolver $installedPackageResolver,
    ) {
    }

    public function findPackageVersion(string $packageName): ?string
    {
        $rootProjectInstalledPackages = $this->installedPackageResolver->resolve(getcwd());

        foreach ($rootProjectInstalledPackages as $rootProjectInstalledPackage) {
            if ($rootProjectInstalledPackage->getName() === $packageName) {
                return $rootProjectInstalledPackage->getVersion();
            }
        }

        return null;
    }
}
