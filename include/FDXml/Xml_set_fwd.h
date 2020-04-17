#ifndef XML_SET_FWD_H
#define XML_SET_FWD_H

#include <type_traits>
#include <set>
#include <unordered_set>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlValue;

    namespace internal
    {
        template<typename T>
        XmlValue serialize_set(T &&s, Serializer &tag);

        template<typename T>
        XmlValue serialize_set(const T &s, Serializer &tag);

        template<typename T, typename ValueType = typename T::value_type>
        bool unserialize_set(const XmlValue &val, T &s, Serializer &tag, std::string *err);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    XmlValue> serialize(Container<T, Compare, Allocator> &&s, Serializer &tag);

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    XmlValue> serialize(const Container<T, Compare, Allocator> &s, Serializer &tag);

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Compare, Allocator> &s, Serializer &tag, std::string *err);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(Container<T, Hash, KeyEqual, Allocator> &&s, Serializer &tag);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(const Container<T, Hash, KeyEqual, Allocator> &s, Serializer &tag);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Hash, KeyEqual, Allocator> &s, Serializer &tag, std::string *err);
}

#endif // XML_SET_FWD_H
