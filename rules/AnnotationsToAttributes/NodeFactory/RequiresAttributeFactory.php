<?php

declare(strict_types=1);

namespace Rector\PHPUnit\AnnotationsToAttributes\NodeFactory;

use PhpParser\Node\AttributeGroup;
use Rector\PhpAttribute\NodeFactory\PhpAttributeGroupFactory;
use Rector\PHPUnit\Enum\PHPUnitAttribute;

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
                $attributeClass = PHPUnitAttribute::REQUIRES_PHP;

                // only version is used, we need to prefix with >=
                if (is_string($attributeValue) && is_numeric($attributeValue[0])) {
                    $attributeValue = '>= ' . $attributeValue;
                }

                $attributeValue = [$attributeValue];
                break;
            case 'PHPUnit':
                $attributeClass = PHPUnitAttribute::REQUIRES_PHPUNIT;

                // only version is used, we need to prefix with >=
                if (is_string($attributeValue) && is_numeric($attributeValue[0])) {
                    $attributeValue = '>= ' . $attributeValue;
                }

                $attributeValue = [$attributeValue];
                break;
            case 'OS':
                $attributeClass = PHPUnitAttribute::REQUIRES_OS;
                $attributeValue = [$attributeValue];
                break;
            case 'OSFAMILY':
                $attributeClass = PHPUnitAttribute::REQUIRES_OS_FAMILY;
                $attributeValue = [$attributeValue];
                break;
            case 'function':
                if (str_contains((string) $attributeValue, '::')) {
                    $attributeClass = PHPUnitAttribute::REQUIRES_METHOD;
                    $attributeValue = explode('::', (string) $attributeValue);
                    $attributeValue[0] .= '::class';
                } else {
                    $attributeClass = PHPUnitAttribute::REQUIRES_FUNCTION;
                    $attributeValue = [$attributeValue];
                }

                break;
            case 'extension':
                $attributeClass = PHPUnitAttribute::REQUIRES_PHP_EXTENSION;
                $attributeValue = explode(' ', (string) $attributeValue, 2);
                break;
            case 'setting':
                $attributeClass = PHPUnitAttribute::REQUIRES_SETTING;
                $attributeValue = explode(' ', (string) $attributeValue, 2);
                break;
            default:
                return null;
        }

        return $this->phpAttributeGroupFactory->createFromClassWithItems($attributeClass, [...$attributeValue]);
    }
}
