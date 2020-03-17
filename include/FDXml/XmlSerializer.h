#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <string>
#include <cstdint>
#include <type_traits>

#include <rapidxml/rapidxml.hpp>
#include <FDXml/Xml_utils.h>


namespace FDXml
{
    struct XmlSerializer
    {
        typedef rapidxml::xml_node<>* Value;

        template<typename T>
        static Value serialize(T &&obj)
        {
            return FDXml::serialize(std::move(obj));
        }

        template<typename T>
        static Value serialize(const T &obj)
        {
            return FDXml::serialize(obj);
        }
    };
}

#endif // XMLSERIALIZER_H
