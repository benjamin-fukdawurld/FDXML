#ifndef XML_SET_H
#define XML_SET_H

#include <FDXml/Xml_set_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    template<typename T>
    XmlValue internal::serialize_set(T &&s, Serializer &tag)
    {
        XmlValue v("array");
        for (auto it = s.begin(), end = s.end(); it != end; ++it)
            v.addChildNode(FDXml::serialize(*it, tag));
        return v;
    }

    template<typename T>
    XmlValue internal::serialize_set(const T &s, Serializer &tag)
    {
        XmlValue v("array");
        for (auto it = s.begin(), end = s.end(); it != end; ++it)
            v.addChildNode(FDXml::serialize(*it, tag));
        return v;
    }

    template<typename T, typename ValueType>
    bool internal::unserialize_set(const XmlValue &val, T &s, Serializer &tag, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
                *err = "Value is not an array";

            return false;
        }

        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            ValueType tmp;
            if(!unserialize(*it, tmp, tag, err))
                return false;

            s.insert(tmp);
        }

        return true;
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    XmlValue> serialize(Container<T, Compare, Allocator> &&s, Serializer &tag)
    {
        return internal::serialize_set(std::forward<Container<T, Compare, Allocator>>(s), tag);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    XmlValue> serialize(const Container<T, Compare, Allocator> &s, Serializer &tag)
    {
        return internal::serialize_set(s, tag);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Compare, Allocator> &s, Serializer &tag, std::string *err)
    {
        return internal::unserialize_set(val, s, tag, err);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(Container<T, Hash, KeyEqual, Allocator> &&s, Serializer &tag)
    {
        return internal::serialize_set(std::forward<Container<T, Hash, KeyEqual, Allocator>>(s), tag);
    }


    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    XmlValue> serialize(const Container<T, Hash, KeyEqual, Allocator> &s, Serializer &tag)
    {
        return internal::serialize_set(s, tag);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Hash, KeyEqual, Allocator> &s, Serializer &tag, std::string *err)
    {
        return internal::unserialize_set(val, s, tag, err);
    }
}

#endif // XML_SET_H
