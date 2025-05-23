#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
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
    static std::string FileChecker(const std::string& str, const std::string& delimiter) 
    {
        
        size_t pos = 0;
        std::string token;
        if ((pos = str.find_last_of(delimiter)) != std::string::npos)
        {
            token = str.substr(pos + 1);
        }
        return token;
    }
    static std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        std::string str = s;  // Make a copy of s to modify
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);

        return tokens;
    }
   
}