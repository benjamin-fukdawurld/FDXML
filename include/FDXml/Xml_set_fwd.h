#ifndef XML_SET_FWD_H
#define XML_SET_FWD_H

#include <type_traits>
#include <string>
#include <set>
#include <unordered_set>

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    namespace internal
    {
        template<typename T>
        struct set_helper
        {
            template<typename Set>
            static rapidxml::xml_node<> *serialize(Set &&s);

            template<typename Set>
            static rapidxml::xml_node<> *serialize(const Set &s);
        };

        template<>
        struct set_helper<std::string>
        {
            template<typename Set>
            static rapidxml::xml_node<> *serialize(Set &&s);

            template<typename Set>
            static rapidxml::xml_node<> *serialize(const Set &s);
        };
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Compare, Allocator> &&i);

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Compare, Allocator> &s);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Hash, KeyEqual, Allocator> &&i);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Hash, KeyEqual, Allocator> &s);
}

#endif // XML_SET_FWD_H
