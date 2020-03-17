#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include <FDXml/Xml_allocator.h>
#include <FDXml/Xml_array_fwd.h>

#include <FDXml/Xml_primitive.h>

namespace FDXml
{
    template<size_t S>
    template<typename T>
    rapidxml::xml_node<> *internal::array_helper<S>::serialize(T &&arr)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "array");
        for(size_t i = 0; i < S; ++i)
        {
            result->append_node(FDXml::serialize<T>(arr[i]));
        }
        return result;
    }

    template<size_t S>
    template<typename T>
    rapidxml::xml_node<> *internal::array_helper<S>::serialize(const T &arr)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "array");
        for(size_t i = 0; i < S; ++i)
        {
            result->append_node(FDXml::serialize<T>(arr[i]));
        }
        return result;
    }

    template<typename T>
    rapidxml::xml_node<> *internal::array_helper<0>::serialize(T &&arr, size_t len)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "array");
        for(size_t i = 0; i < len; ++i)
        {
            result->append_node(FDXml::serialize<T>(arr[i]));
        }
        return result;
    }

    template<typename T>
    rapidxml::xml_node<> *internal::array_helper<0>::serialize(const T &arr, size_t len)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "array");
        for(size_t i = 0; i < len; ++i)
        {
            result->append_node(FDXml::serialize<T>(arr[i]));
        }
        return result;
    }

    template<typename T>
    rapidxml::xml_node<> *serialize(const T arr[], size_t len)
    {
        return internal::array_helper<0>::serialize(arr, len);
    }

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(const T arr[])
    {
        return internal::array_helper<N>::serialize(arr);
    }

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(std::array<T, N> &&arr)
    {
        return internal::array_helper<N>::serialize(arr);
    }

    template<typename T, size_t N>
    rapidxml::xml_node<> *serialize(const std::array<T, N> &arr)
    {
        return internal::array_helper<N>::serialize(arr);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Allocator> &&arr)
    {
        return internal::array_helper<0>::serialize(arr, arr.size);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Allocator> &arr)
    {
        return internal::array_helper<0>::serialize(arr, arr.size);
    }
}

#endif // XML_ARRAY_H
