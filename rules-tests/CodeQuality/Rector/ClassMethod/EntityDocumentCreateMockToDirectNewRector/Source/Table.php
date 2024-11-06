<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector\Source;

use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity
 */
class Table
{
    private bool $isLocked;

    public function setLocked(bool $locked): void
    {
        $this->isLocked = $locked;
    }

    public function isLocked(): bool
    {
        return $this->isLocked;
    }
}
