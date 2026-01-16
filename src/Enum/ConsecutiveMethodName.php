<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Enum;

final class ConsecutiveMethodName
{
    public const string WILL_RETURN_ON_CONSECUTIVE_CALLS = 'willReturnOnConsecutiveCalls';

    public const string WILL_RETURN_ARGUMENT = 'willReturnArgument';

    public const string WILL_RETURN_SELF = 'willReturnSelf';

    public const string WILL_THROW_EXCEPTION = 'willThrowException';

    public const string WILL_RETURN_REFERENCE = 'willReturnReference';

    public const string WILL_RETURN = 'willReturn';

    public const string WILL_RETURN_CALLBACK = 'willReturnCallback';

    public const string WITH_CONSECUTIVE = 'withConsecutive';
}
