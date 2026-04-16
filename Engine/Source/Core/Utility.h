#pragma once

namespace GameEngine
{
	class NonCopyabel
    {
    protected:
        NonCopyabel() = default;
        ~NonCopyabel() = default;

        NonCopyabel(const NonCopyabel&) = default;
        NonCopyabel& operator=(const NonCopyabel&) = default;

        NonCopyabel(NonCopyabel&&) = default;
        NonCopyabel& operator=(NonCopyabel&&) = default;
    };
}

#if defined(_MSC_VER)
#define PLATFORM_BREAK() __debugbreak()
#else
#include <signal.h>
#define PLATFORM_BREAK() raise(SIGTRAP);
#endif