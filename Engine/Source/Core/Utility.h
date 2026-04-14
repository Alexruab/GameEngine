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

    #define PLATFORM_BREAK() (__nop(), __debugbreak());
}