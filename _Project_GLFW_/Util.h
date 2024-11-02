#pragma once
#include <algorithm>
#include <iterator>

namespace UTils
{
    template <typename Container, typename T>
    bool Contains(const Container& container, const T& value)
    {
        return std::find(std::begin(container), std::end(container), value) != std::end(container);
    }
}