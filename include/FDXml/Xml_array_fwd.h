#ifndef XML_ARRAY_FWD_H
#define XML_ARRAY_FWD_H

#include <array>
#include <vector>
#include <deque>

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    namespace internal
    {
        template<size_t S>
        struct array_helper
        {
            template<typename T>
            static rapidxml::xml_node<> *serialize(T &&arr);

            template<typename T>
            static rapidxml::xml_node<> *serialize(const T &arr);
        };

        template<>
        struct array_helper<0>
        {
            template<typename T>
            static rapidxml::xml_node<> *serialize(T &&arr, size_t len);

            template<typename T>
            static rapidxml::xml_node<> *serialize(const T &arr, size_t len);
        };
    }

    template<typename T>
    rapidxml::xml_node<> *serialize(const T arr[], size_t len);

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(const T arr[]);

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(std::array<T, N> &&arr);

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(const std::array<T, N> &arr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Allocator> &&arr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Allocator> &arr);
}

#endif // XML_ARRAY_FWD_H
