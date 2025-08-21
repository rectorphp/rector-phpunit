<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Symfony\Component\Form\FormInterface;

final class SkipReturnCreateMock extends TestCase
{
    public function test($value): void
    {
        $form = $this->createMock(FormInterface::class);

        $form->method('add')
            ->willReturnCallback(function ($name, $type, $options) use (&$calls) {
                 $calls[] = compact('name', 'type', 'options');
                 return $this->createMock(FormInterface::class);
             });
    }
}
