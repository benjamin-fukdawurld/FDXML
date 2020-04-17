#ifndef XML_TUPLE_FWD_H
#define XML_TUPLE_FWD_H

#include <tuple>

#include <FDXml/FDXml.h>

namespace FDXml
{
    class XmlValue;

    namespace internal
    {
        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, XmlValue &val, Serializer &tag);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, XmlValue &val, Serializer &tag);

        template<typename... Args>
        XmlValue serialize_tuple(const std::tuple<Args...> &t, Serializer &tag);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        bool> unserialize_tuple(const XmlValue &val, std::tuple<Args...> &t, Serializer &tag, std::string *err = nullptr);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        bool> unserialize_tuple(const XmlValue &val, std::tuple<Args...> &t, Serializer &tag, std::string *err = nullptr);
    }

    template<typename First, typename Second>
    XmlValue serialize(std::pair<First, Second> &&p, Serializer &tag);

    template<typename First, typename Second>
    XmlValue serialize(const std::pair<First, Second> &p, Serializer &tag);

    template<typename First, typename Second>
    bool unserialize(const XmlValue &val, std::pair<First, Second> &p, Serializer &tag, std::string *err = nullptr);

    template<typename ...Args>
    XmlValue serialize(std::tuple<Args...> &&t, Serializer &tag);

    template<typename ...Args>
    XmlValue serialize(const std::tuple<Args...> &t, Serializer &tag);

    template<typename ...Args>
    bool unserialize(const XmlValue &val, std::tuple<Args...> &t, Serializer &tag, std::string *err = nullptr);
}

#endif // XML_TUPLE_FWD_H
