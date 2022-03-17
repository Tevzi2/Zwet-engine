#pragma once

#include <core.h>

namespace ZWET 
{
    // funkcije za ustvarjanje Unique in Shared smart pointerjev (pametnih kazalcev)
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr UniquePtr<T> CreateUnique (Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr SharedPtr<T> CreateShared (Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}