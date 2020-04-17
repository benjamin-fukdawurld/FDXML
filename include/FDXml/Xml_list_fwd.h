#ifndef XML_LIST_FWD_H
#define XML_LIST_FWD_H

#include <type_traits>

#include <list>
#include <forward_list>
#include <initializer_list>

#include <string>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlValue;

    namespace internal
    {
        template<typename T>
        XmlValue serialize_list(T &&l, Serializer &serializer);

        template<typename T>
        XmlValue serialize_list(const T &l, Serializer &serializer);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    XmlValue> serialize(Container<T, Allocator> &&l, Serializer &serializer);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    XmlValue> serialize(const Container<T, Allocator> &l, Serializer &serializer);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Allocator> &l, Serializer &serializer, std::string *err);

    template<typename T>
    XmlValue serialize(std::initializer_list<T> &&l, Serializer &serializer);

    template<typename T>
    XmlValue serialize(const std::initializer_list<T> &l, Serializer &serializer);
}

#endif // XML_LIST_FWD_H
