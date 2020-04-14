#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <FDSerialize/SerializerBase.h>

#include <rapidxml/rapidxml.hpp>
#include <FDXml/Xml_utils.h>


namespace FDXml
{
    struct XmlSerializerImpl
    {
        typedef rapidxml::xml_node<>* Value;

        template<typename T>
        static Value serialize(T &&obj)
        {
            return FDXml::serialize(std::forward<T>(obj));
        }

        template<typename T>
        static Value serialize(const T &obj)
        {
            return FDXml::serialize(obj);
        }

        template<typename T>
        static Value serialize(T obj[], size_t len)
        {
            return FDXml::serialize(obj, len);
        }

        template<typename T>
        static bool unserialize(const Value &val, T &out, std::string *err = nullptr)
        {
            return false;
            //return FDXml::unserialize(val, out, err);
        }

        template<typename T>
        static bool unserialize(const Value &val, T out[], size_t len, std::string *err = nullptr)
        {
            return false;
            //return FDXml::unserialize(val, out, len, err);
        }
    };

    typedef FDSerialize::SerializerBase<XmlSerializerImpl> Serializer;
}

#endif // XMLSERIALIZER_H
