#ifndef XML_LIST_FWD_H
#define XML_LIST_FWD_H

#include <list>
#include <forward_list>
#include <type_traits>

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Allocator> &&i);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Allocator> &i);
}

#endif // XML_LIST_FWD_H
