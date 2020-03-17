#ifndef XML_PRIMITIVE_FWD_H
#define XML_PRIMITIVE_FWD_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <type_traits>

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    rapidxml::xml_attribute<> *serialize_attribute(const char *name, std::nullptr_t);

    rapidxml::xml_attribute<> *serialize_attribute(const char *name, const char c);

    rapidxml::xml_attribute<> *serialize_attribute(const char *name, const char *c);

    rapidxml::xml_attribute<> *serialize_attribute(const char *name, std::string &&c);

    rapidxml::xml_attribute<> *serialize_attribute(const char *name, const std::string &c);

    rapidxml::xml_attribute<> *serialize_attribute(const char *name, const bool b);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, const T &i);

    rapidxml::xml_node<> *serialize(const char c);

    rapidxml::xml_node<> *serialize(const char *c);

    rapidxml::xml_node<> *serialize(std::string &&c);

    rapidxml::xml_node<> *serialize(const std::string &c);

    rapidxml::xml_node<> *serialize(const bool b);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_node<> *> serialize(T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_node<> *> serialize(const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_node<> *> serialize(T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_node<> *> serialize(const T &i);
}

#endif // XML_PRIMITIVE_FWD_H
