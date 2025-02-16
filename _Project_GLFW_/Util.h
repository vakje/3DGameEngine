#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

namespace UTils
{
    //somehow only works when i use functions with template inline or static uknown technologies for me
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
    static std::string SplitString(const std::string& str, const std::string& delimiter) 
    {
        
        size_t pos = 0;
        std::string token;
        if ((pos = str.find_last_of(delimiter)) != std::string::npos)
        {
            token = str.substr(pos + 1);
        }
        return token;
    }
   
}