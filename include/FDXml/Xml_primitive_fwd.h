#ifndef XML_PRIMITIVE_FWD_H
#define XML_PRIMITIVE_FWD_H

#include <cstdint>
#include <string>
#include <type_traits>
#include <optional>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlAttribute;
    class XmlValue;

    template<typename T>
    bool unserialize_attribute(const XmlAttribute &attr, std::optional<T> &opt, Serializer &serializer, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, std::nullptr_t, Serializer &serializer);

    XmlAttribute serialize_attribute(const char *name, const char c, Serializer &serializer);

    bool unserialize_attribute(const XmlAttribute &attr, char &c, Serializer &serializer, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, const char *c, Serializer &serializer);

    XmlAttribute serialize_attribute(const char *name, std::string &&c, Serializer &serializer);

    XmlAttribute serialize_attribute(const char *name, const std::string &c, Serializer &serializer);

    bool unserialize_attribute(const XmlAttribute &attr, std::string &c, Serializer &serializer, std::string *err = nullptr);

    XmlAttribute serialize_attribute(const char *name, const bool b, Serializer &serializer);

    bool unserialize_attribute(const XmlAttribute &attr, bool &c, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, T &&i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, const T &i, Serializer &serializer);

    bool unserialize_attribute(const XmlAttribute &attr, int64_t &i, Serializer &serializer, std::string *err = nullptr);
    bool unserialize_attribute(const XmlAttribute &attr, uint64_t &i, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value
                || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &i, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute > serialize_attribute(const char *name, T &&i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute > serialize_attribute(const char *name, const T &i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value || std::is_same<T, double>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &f, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    bool unserialize(const XmlValue &val, std::optional<T> &opt, Serializer &serializer, std::string *err = nullptr);

    XmlValue serialize(const char c, Serializer &serializer);

    XmlValue serialize(const char *c, Serializer &serializer);

    XmlValue serialize(std::string &&c, Serializer &serializer);

    XmlValue serialize(const std::string &c, Serializer &serializer);

    XmlValue serialize(const bool b, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlValue > serialize(T &&i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlValue > serialize(const T &i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue > serialize(T &&i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue > serialize(const T &i, Serializer &serializer);

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
    bool> unserialize(const XmlValue &val, T &f, Serializer &serializer, std::string *err = nullptr);
}

#endif // XML_PRIMITIVE_FWD_H
