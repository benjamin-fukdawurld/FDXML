#ifndef XML_LIST_H
#define XML_LIST_H

#include <FDXml/Xml_list_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    namespace internal
    {
        template<typename T>
        XmlValue serialize_list(T &&l, Serializer &tag)
        {
            XmlValue v("array");
            for (auto it = l.begin(), end = l.end(); it != end; ++it)
                v.addChildNode(FDXml::serialize(*it, tag));
            return v;
        }

        template<typename T>
        XmlValue serialize_list(const T &l, Serializer &tag)
        {
            XmlValue v("array");
            for (auto it = l.begin(), end = l.end(); it != end; ++it)
                v.addChildNode(FDXml::serialize(*it, tag));
            return v;
        }
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    XmlValue> serialize(Container<T, Allocator> &&l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    XmlValue> serialize(const Container<T, Allocator> &l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Allocator> &l, Serializer &tag, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
            {
                *err = "Value is not an array";
            }

            return false;
        }

        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            T tmp;
            if(!unserialize(*it, tmp, tag, err))
                return false;

            l.push_back(std::move(tmp));
        }

        return true;
    }

    template<typename T>
    XmlValue serialize(std::initializer_list<T> &&l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }

    template<typename T>
    XmlValue serialize(const std::initializer_list<T> &l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }
}

#endif // XML_LIST_H
