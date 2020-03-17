#ifndef XML_SET_H
#define XML_SET_H

#include <FDXml/Xml_allocator.h>
#include <FDXml/Xml_set_fwd.h>

#include <FDXml/Xml_primitive.h>

namespace FDXml
{
    template<typename T>
    template<typename Set>
    rapidxml::xml_node<> *internal::set_helper<T>::serialize(Set &&s)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "set");
        for(auto it = s.begin(), end = s.end(); it != end; ++it)
        {
            result->append_node(FDXml::serialize<T>(*it));
        }
        return result;
    }

    template<typename T>
    template<typename Set>
    rapidxml::xml_node<> *internal::set_helper<T>::serialize(const Set &s)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "set");
        for(auto it = s.begin(), end = s.end(); it != end; ++it)
        {
            result->append_node(FDXml::serialize<T>(*it));
        }
        return result;
    }



    template<typename Set>
    rapidxml::xml_node<> *internal::set_helper<std::string>::serialize(Set &&s)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "set");
        for(auto it = s.begin(), end = s.end(); it != end; ++it)
        {
            result->append_attribute(FDXml::serialize_attribute(it->c_str(), nullptr));
        }
        return result;
    }

    template<typename Set>
    rapidxml::xml_node<> *internal::set_helper<std::string>::serialize(const Set &s)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "set");
        for(auto it = s.begin(), end = s.end(); it != end; ++it)
        {
            result->append_attribute(FDXml::serialize_attribute(it->c_str(), nullptr));
        }
        return result;
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Compare, Allocator> &&s)
    {
        return internal::set_helper<T>::serialize(s);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Compare, Allocator> &s)
    {
        return internal::set_helper<T>::serialize(s);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<T, Hash, KeyEqual, Allocator> &&s)
    {
        return internal::set_helper<T>::serialize(s);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<T, Hash, KeyEqual, Allocator> &s)
    {
        return internal::set_helper<T>::serialize(s);
    }
}

#endif // XML_SET_H
