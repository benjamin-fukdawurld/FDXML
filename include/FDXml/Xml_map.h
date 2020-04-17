#ifndef XML_MAP_H
#define XML_MAP_H

#include <FDXml/Xml_map_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    template<typename Key, typename Value>
    template<typename Map>
    XmlValue internal::map_helper<Key, Value>::serialize(Map &&m, Serializer &tag)
    {
        XmlValue result("map", "array");
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            XmlValue item("item");
            XmlValue key = FDXml::serialize(it->first, tag);
            key.setName("key");
            XmlValue value = FDXml::serialize(it->second, tag);
            value.setName("value");

            item.addChildNode(key);
            item.addChildNode(value);
            result.addChildNode(item);
        }

        return result;
    }


    template<typename Key, typename Value>
    template<typename Map>
    XmlValue internal::map_helper<Key, Value>::serialize(const Map &m, Serializer &tag)
    {
        XmlValue result("map", "array");
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            XmlValue item("item");
            XmlValue key = FDXml::serialize(it->first, tag);
            key.setName("key");
            XmlValue value = FDXml::serialize(it->second, tag);
            value.setName("value");

            item.addChildNode(key);
            item.addChildNode(value);
            result.addChildNode(item);
        }

        return result;
    }

    template<typename  Key, typename Value>
    template<typename Map>
    bool internal::map_helper<Key, Value>::unserialize(const XmlValue &val, Map &m, Serializer &tag, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
                *err = "Value is not an array";

            return false;
        }

        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            XmlValue key = val["key"];
            if(!key)
            {
                if(err)
                    *err = "Value has no member 'key'";

                return false;
            }

            XmlValue value = val["value"];
            if(!value)
            {
                if(err)
                    *err = "Value has no member 'value'";

                return false;
            }

            Key k;
            Value v;
            if(!FDXml::unserialize(key, k, tag, err) || !FDXml::unserialize(value, v, tag, err))
                return false;

            m.emplace(k, v);
        }

        return true;
    }

    template<typename Value>
    template<typename Map>
    XmlValue internal::map_helper<std::string, Value>::serialize(Map &&m, Serializer &tag)
    {
        XmlValue result("map");
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            XmlValue item = FDXml::serialize(it->second, tag);
            item.setName(it->first);
            result.addChildNode(item);
        }

        return result;
    }

    template<typename Value>
    template<typename Map>
    XmlValue internal::map_helper<std::string, Value>::serialize(const Map &m, Serializer &tag)
    {
        XmlValue result("map");
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            XmlValue item = FDXml::serialize(it->second, tag);
            item.setName(it->first);
            result.addChildNode(item);
        }

        return result;
    }

    template<typename Value>
    template<typename Map>
    bool internal::map_helper<std::string, Value>::unserialize(const XmlValue &val, Map &m, Serializer &tag, std::string *err)
    {
        if(!val.isObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            Value v;
            if(!FDXml::unserialize(*it, v, tag, err))
                return false;

            m.emplace(it->getAttribute("key"), v);
        }

        return true;
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    XmlValue> serialize(Container<Key, Value, Compare, Allocator> &&m, Serializer &tag)
    {
        return internal::map_helper<Key, Value>::serialize(std::forward<Container<Key, Value, Compare, Allocator>>(m), tag);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    XmlValue> serialize(const Container<Key, Value, Compare, Allocator> &m, Serializer &tag)
    {
        return internal::map_helper<Key, Value>::serialize(m, tag);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<Key, Value, Compare, Allocator> &m, Serializer &tag, std::string *err)
    {
        return internal::map_helper<Key, Value>::unserialize(val, m, tag, err);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(Container<Key, Value, Hash, KeyEqual, Allocator> &&m, Serializer &tag)
    {
        return internal::map_helper<Key, Value>::serialize(std::forward<Container<Key, Value, Hash, KeyEqual, Allocator>>(m), tag);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &m, Serializer &tag)
    {
        return internal::map_helper<Key, Value>::serialize(m, tag);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<Key, Value, Hash, KeyEqual, Allocator> &m, Serializer &tag, std::string *err)
    {
        return internal::map_helper<Key, Value>::unserialize(val, m, tag, err);
    }
}

#endif // XML_MAP_H
