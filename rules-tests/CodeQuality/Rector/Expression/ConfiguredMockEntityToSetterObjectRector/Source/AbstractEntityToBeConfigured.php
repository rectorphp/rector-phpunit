<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector\Source;

use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity()]
abstract class AbstractEntityToBeConfigured
{
    private string $name = '';

    public function setName($name)
    {
        $this->name = $name;
    }

    public function getName(): string
    {
        return $this->name;
    }
}
