#ifndef XML_MAP_H
#define XML_MAP_H

#include <FDXml/Xml_allocator.h>
#include <FDXml/Xml_map_fwd.h>

#include <FDXml/Xml_primitive.h>

namespace FDXml
{
        template<typename Key, typename Value>
        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<Key, Value>::serialize(Map &&m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element, "item");
                rapidxml::xml_node<> *key = Xml_helper::allocator.allocate_node(rapidxml::node_element, "key");
                key->append_node(FDXml::serialize(it->first));
                item->append_node(key);
                item->append_node(FDXml::serialize(it->second));
                result->append_node(item);
            }
            return result;
        }

        template<typename Key, typename Value>
        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<Key, Value>::serialize(const Map &m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element, "item");
                rapidxml::xml_node<> *key = Xml_helper::allocator.allocate_node(rapidxml::node_element, "key");
                key->append_node(FDXml::serialize(it->first));
                item->append_node(key);
                item->append_node(FDXml::serialize(it->second));
                result->append_node(item);
            }
            return result;
        }


        template<typename Value>
        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<std::string, Value>::serialize(Map &&m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                                                 Xml_helper::allocator.allocate_string(it->first.c_str()));
                item->append_node(FDXml::serialize(it->second));
                result->append_node(item);
            }
            return result;
        }

        template<typename Value>
        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<std::string, Value>::serialize(const Map &m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                                                 Xml_helper::allocator.allocate_string(it->first.c_str()));
                item->append_node(FDXml::serialize(it->second));
                result->append_node(item);
            }
            return result;
        }

        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<std::string, std::string>::serialize(Map &&m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                                                 Xml_helper::allocator.allocate_string(it->first.c_str()));
                item->append_attribute(FDXml::serialize_attribute("value", it->second));
                result->append_node(item);
            }
            return result;
        }

        template<typename Map>
        rapidxml::xml_node<> *internal::map_helper<std::string, std::string>::serialize(const Map &m)
        {
            rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "map");
            for(auto it = m.begin(), end = m.end(); it != end; ++it)
            {
                rapidxml::xml_node<> *item = Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                                                 Xml_helper::allocator.allocate_string(it->first.c_str()));
                item->append_attribute(FDXml::serialize_attribute("value", it->second));
                result->append_node(item);
            }
            return result;
        }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<Key, Value, Compare, Allocator> &&m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<Key, Value, Compare, Allocator> &m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(Container<Key, Value, Hash, KeyEqual, Allocator> &&m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidxml::xml_node<> *> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }
}

#endif // XML_MAP_H
