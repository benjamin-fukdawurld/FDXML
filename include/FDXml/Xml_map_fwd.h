#ifndef XML_MAP_FWD_H
#define XML_MAP_FWD_H

#include <type_traits>
#include <map>
#include <unordered_map>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlValue;

    namespace internal
    {
        template<typename Key, typename Value>
        struct map_helper
        {
            template<typename Map>
            static XmlValue serialize(Map &&m, Serializer &tag);

            template<typename Map>
            static XmlValue serialize(const Map &m, Serializer &tag);

            template<typename Map>
            static bool unserialize(const XmlValue &val, Map &m, Serializer &tag, std::string *err = nullptr);
        };

        template<typename Value>
        struct map_helper<std::string, Value>
        {
            template<typename Map>
            static XmlValue serialize(Map &&m, Serializer &tag);

            template<typename Map>
            static XmlValue serialize(const Map &m, Serializer &tag);

            template<typename Map>
            static bool unserialize(const XmlValue &val, Map &m, Serializer &tag, std::string *err = nullptr);
        };
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    XmlValue> serialize(Container<Key, Value, Compare, Allocator> &&i, Serializer &tag);

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    XmlValue> serialize(const Container<Key, Value, Compare, Allocator> &i, Serializer &tag);

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<Key, Value, Compare, Allocator> &m, Serializer &tag, std::string *err = nullptr);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(Container<Key, Value, Hash, KeyEqual, Allocator> &&i, Serializer &tag);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &i, Serializer &tag);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<Key, Value, Hash, KeyEqual, Allocator> &m, Serializer &tag, std::string *err = nullptr);
}

#endif // XML_MAP_FWD_H
