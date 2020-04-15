#ifndef XML_PRIMITIVE_FWD_H
#define XML_PRIMITIVE_FWD_H

#include <cstdint>
#include <string>
#include <type_traits>
#include <optional>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

namespace FDXml
{
    template<typename T>
    bool unserialize_attribute(const XmlAttribute &attr, std::optional<T> &opt, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, std::nullptr_t);

    XmlAttribute serialize_attribute(const char *name, const char c);

    bool unserialize_attribute(const XmlAttribute &attr, char &c, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, const char *c);

    XmlAttribute serialize_attribute(const char *name, std::string &&c);

    XmlAttribute serialize_attribute(const char *name, const std::string &c);

    bool unserialize_attribute(const XmlAttribute &attr, std::string &c, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, const bool b);

    bool unserialize_attribute(const XmlAttribute &attr, bool &c, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, const T &i);

    bool unserialize_attribute(const XmlAttribute &attr, int64_t &i, std::string *err = nullptr);
    bool unserialize_attribute(const XmlAttribute &attr, uint64_t &i, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value
                || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &i, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute > serialize_attribute(const char *name, T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute > serialize_attribute(const char *name, const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value || std::is_same<T, double>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, float &f, std::string *err = nullptr);

    XmlValue serialize(const char c);

    FDXml::XmlValue serialize(const char *c);

    FDXml::XmlValue serialize(std::string &&c);

    FDXml::XmlValue serialize(const std::string &c);

    FDXml::XmlValue serialize(const bool b);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    FDXml::XmlValue > serialize(T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    FDXml::XmlValue > serialize(const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    FDXml::XmlValue > serialize(T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    FDXml::XmlValue > serialize(const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, bool>::value
                        || std::is_same<T, char>::value
                        || std::is_same<T, std::string>::value
                        || std::is_same<T, int16_t>::value
                        || std::is_same<T, int32_t>::value
                        || std::is_same<T, int64_t>::value
                        || std::is_same<T, uint16_t>::value
                        || std::is_same<T, uint32_t>::value
                        || std::is_same<T, uint64_t>::value
                        ||std::is_same<T, float>::value
                        || std::is_same<T, double>::value,
    bool> unserialize(const FDXml::XmlValue &val, T &f, std::string *err = nullptr);
}

#endif // XML_PRIMITIVE_FWD_H
