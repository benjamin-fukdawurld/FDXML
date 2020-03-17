#ifndef XML_PRIMITIVE_H
#define XML_PRIMITIVE_H

#include <rapidxml/rapidxml.hpp>

#include <FDXml/Xml_allocator.h>
#include <FDXml/Xml_primitive_fwd.h>

namespace FDXml
{
    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, T &&i)
    {
        return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                        Xml_helper::allocator.allocate_string(std::to_string(i).c_str()));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, const T &i)
    {
        return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                        Xml_helper::allocator.allocate_string(std::to_string(i).c_str()));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, T &&i)
    {
        return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                        Xml_helper::allocator.allocate_string(std::to_string(i).c_str()));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_attribute<> *> serialize_attribute(const char *name, const T &i)
    {
        return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                        Xml_helper::allocator.allocate_string(std::to_string(i).c_str()));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_node<> *> serialize(T &&i)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "int");
        result->append_attribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_node<> *> serialize(const T &i)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "int");
        result->append_attribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_node<> *> serialize(T &&i)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "float");
        result->append_attribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    rapidxml::xml_node<> *> serialize(const T &i)
    {
        rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "float");
        result->append_attribute(serialize_attribute("value", i));
        return result;
    }
}

#endif // XML_PRIMITIVE_H
