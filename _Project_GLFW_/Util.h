#pragma once
#include <algorithm>
#include <iterator>
#include <map>

namespace UTils
{
    template <typename Container, typename T>
    bool Contains(const Container& container, const T& value)
    {
        return std::find(std::begin(container), std::end(container), value) != std::end(container);
    }
    template<typename K,typename V>
    void InsertElement(std::map<K, V>& m_map, const K& key, const V& value) 
    {
        m_map[key] = value;
        std::cout << "inserted [" << key << "," << value << "]" << std::endl;

    }
}