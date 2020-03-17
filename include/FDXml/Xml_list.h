#ifndef XML_LIST_H
#define XML_LIST_H

#include <FDXml/Xml_allocator.h>
#include <FDXml/Xml_list_fwd.h>

namespace FDXml
{
    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Allocator> &&l)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "list");
        for(auto it = l.begin(), end = l.end(); it != end; ++it)
        {
            result->append_node(serialize<T>(*it));
        }
        return result;
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Allocator> &l)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "list");
        for(auto it = l.begin(), end = l.end(); it != end; ++it)
        {
            result->append_node(serialize<T>(*it));
        }
        return result;
    }
}

#endif // XML_LIST_H
