#ifndef XML_MAP_FWD_H
#define XML_MAP_FWD_H

#include <string>
#include <map>
#include <unordered_map>
#include <type_traits>

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    namespace internal
    {
        template<typename Key, typename Value>
        struct map_helper
        {
            template<typename Map>
            static rapidxml::xml_node<> *serialize(Map &&m);

            template<typename Map>
            static rapidxml::xml_node<> *serialize(const Map &m);
        };

        template<typename Value>
        struct map_helper<std::string, Value>
        {
            template<typename Map>
            static rapidxml::xml_node<> *serialize(Map &&m);

            template<typename Map>
            static rapidxml::xml_node<> *serialize(const Map &m);
        };

        template<>
        struct map_helper<std::string, std::string>
        {
            template<typename Map>
            static rapidxml::xml_node<> *serialize(Map &&m);

            template<typename Map>
            static rapidxml::xml_node<> *serialize(const Map &m);
        };
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<Key, Value, Compare, Allocator> &&i);

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<Key, Value, Compare, Allocator> &i);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<Key, Value, Hash, KeyEqual, Allocator> &&i);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &i);
}

#endif // XML_MAP_FWD_H
