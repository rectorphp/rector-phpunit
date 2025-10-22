<?php

declare(strict_types=1);

namespace Rector\PHPUnit\AnnotationsToAttributes\NodeFactory;

use PhpParser\Node\AttributeGroup;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;

final readonly class RequiresAttributeFactory
{
    public function __construct(
        private PhpAttributeGroupFactory $phpAttributeGroupFactory
    ) {
    }

    public function create(string $annotationValue): ?AttributeGroup
    {
        $annotationValues = explode(' ', $annotationValue, 2);

        $type = array_shift($annotationValues);
        $attributeValue = array_shift($annotationValues);

        switch ($type) {
            case 'PHP':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresPhp';
                $attributeValue = [$attributeValue];
                break;
            case 'PHPUnit':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresPhpunit';
                $attributeValue = [$attributeValue];
                break;
            case 'OS':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresOperatingSystem';
                $attributeValue = [$attributeValue];
                break;
            case 'OSFAMILY':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily';
                $attributeValue = [$attributeValue];
                break;
            case 'function':
                if (str_contains((string) $attributeValue, '::')) {
                    $attributeClass = 'PHPUnit\Framework\Attributes\RequiresMethod';
                    $attributeValue = explode('::', (string) $attributeValue);
                    $attributeValue[0] .= '::class';
                } else {
                    $attributeClass = 'PHPUnit\Framework\Attributes\RequiresFunction';
                    $attributeValue = [$attributeValue];
                }

                break;
            case 'extension':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresPhpExtension';
                $attributeValue = explode(' ', (string) $attributeValue, 2);
                break;
            case 'setting':
                $attributeClass = 'PHPUnit\Framework\Attributes\RequiresSetting';
                $attributeValue = explode(' ', (string) $attributeValue, 2);
                break;
            default:
                return null;
        }

        return $this->phpAttributeGroupFactory->createFromClassWithItems($attributeClass, [...$attributeValue]);
    }
}
