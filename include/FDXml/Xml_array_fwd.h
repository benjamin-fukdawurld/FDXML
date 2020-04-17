#ifndef XML_ARRAY_FWD_H
#define XML_ARRAY_FWD_H

#include <array>
#include <vector>
#include <deque>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlValue;

    namespace internal
    {
        template<size_t S>
        struct array_helper
        {
            template<typename T>
            static XmlValue serialize(T &&arr, Serializer &serializer);

            template<typename T>
            static XmlValue serialize(const T &arr, Serializer &serializer);

            template<typename T>
            static bool unserialize(const XmlValue &val, T &arr, Serializer &serializer, std::string *err = nullptr);
        };

        template<>
        struct array_helper<0>
        {
            template<typename T>
            static XmlValue serialize(T &&arr, size_t len, Serializer &serializer);

            template<typename T>
            static XmlValue serialize(const T &arr, size_t len, Serializer &serializer);

            template<typename T>
            static bool unserialize(const XmlValue &val, T &arr, size_t len, Serializer &serializer, std::string *err = nullptr);

            template<typename T>
            static bool unserialize(const XmlValue &val, T &arr, Serializer &serializer, std::string *err = nullptr);
        };
    }

    template<typename T>
    XmlValue serialize(const T arr[], size_t len, Serializer &serializer);

    template<typename T>
    bool unserialize(const XmlValue &val, T arr[], size_t len, Serializer &serializer, std::string *err = nullptr);

    template<typename T, size_t N>
    XmlValue serialize(const T arr[], Serializer &serializer);

    template<typename T, size_t N>
    bool unserialize(const XmlValue &val, T arr[], Serializer &serializer, std::string *err = nullptr);

    template<typename T, size_t N>
    XmlValue serialize(std::array<T, N> &&arr, Serializer &serializer);

    template<typename T, size_t N>
    XmlValue serialize(const std::array<T, N> &arr, Serializer &serializer);

    template<typename T, size_t N>
    bool unserialize(const XmlValue &val, std::array<T, N> &arr, Serializer &serializer, std::string *err = nullptr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    XmlValue > serialize(Container<T, Allocator> &&arr, Serializer &serializer);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    XmlValue > serialize(const Container<T, Allocator> &arr, Serializer &serializer);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Allocator> &arr, Serializer &serializer, std::string *err = nullptr);
}

#endif // XML_ARRAY_FWD_H
