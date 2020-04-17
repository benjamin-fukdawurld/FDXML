#ifndef XML_TUPLE_H
#define XML_TUPLE_H

#include <FDXml/Xml_tuple_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    namespace internal
    {
        template<std::size_t I, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &, XmlValue &, Serializer &)
        {}

        template<std::size_t I, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, XmlValue &val, Serializer &serializer)
        {
            val.addChildNode(FDXml::serialize(std::get<I>(t), serializer));
            serialize_tuple<I + 1, Args...>(t, val, serializer);
        }

        template<typename... Args>
        XmlValue serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer)
        {
            XmlValue val("array", serializer);

            serialize_tuple<0, Args...>(t, val, serializer);

            return val;
        }

        template<std::size_t I, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        bool> unserialize_tuple(const XmlValue &, std::tuple<Args...> &, Serializer &, std::string *)
        {
            return true;
        }

        template<std::size_t I, typename...Args>
        std::enable_if_t<I < sizeof...(Args),
        bool> unserialize_tuple(const XmlValue &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err)
        {
            if(!val.isArray())
            {
                if(err)
                {
                    *err = "Value is not an array";
                }

                return false;
            }

            if(val.size() != sizeof...(Args))
            {
                if(err)
                {
                    *err = std::string("Value is not an array of size ") + std::to_string(sizeof...(Args));
                }

                return false;
            }

            return FDXml::unserialize(val[I], std::get<I>(t), serializer, err) && unserialize_tuple<I + 1, Args...>(val, t, serializer, err);
        }
    }

    template<typename First, typename Second>
    XmlValue serialize(std::pair<First, Second> &&p, Serializer &serializer)
    {
        XmlValue val("pair", serializer);
        XmlValue first(FDXml::serialize(p.first, serializer));
        first.setName("first");

        XmlValue second(FDXml::serialize(p.second, serializer));
        second.setName("second");

        val.addChildNode(first);
        val.addChildNode(second);

        return val;
    }

    template<typename First, typename Second>
    XmlValue serialize(const std::pair<First, Second> &p, Serializer &serializer)
    {
        XmlValue val("pair", serializer);
        XmlValue first(FDXml::serialize(p.first, serializer));
        first.setName("first");

        XmlValue second(FDXml::serialize(p.second, serializer));
        second.setName("second");

        val.addChildNode(first);
        val.addChildNode(second);

        return val;
    }

    template<typename First, typename Second>
    bool unserialize(const XmlValue &val, std::pair<First, Second> &p, Serializer &serializer, std::string *err)
    {
        if(!val.isObject())
        {
            if(err)
            {
                *err = "Value is not an object";
            }

            return false;
        }

        if(!val.hasChildNode("first"))
        {
            if(err)
            {
                *err = "Value has no member named 'first'";
            }

            return false;
        }

        if(!val.hasChildNode("second"))
        {
            if(err)
            {
                *err = "Value has no member named 'second'";
            }

            return false;
        }

        return unserialize(val["first"], p.first, serializer, err) && unserialize(val["second"], p.second, serializer, err);
    }

    template<typename ...Args>
    XmlValue serialize(std::tuple<Args...> &&t, Serializer &serializer)
    {
        using namespace FDXml::internal;
        return serialize_tuple(t, serializer);
    }

    template<typename ...Args>
    XmlValue serialize(const std::tuple<Args...> &t, Serializer &serializer)
    {
        using namespace FDXml::internal;
        return serialize_tuple(t, serializer);
    }

    template<typename...Args>
    bool unserialize(const XmlValue &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err)
    {
        using namespace FDXml::internal;
        return unserialize_tuple(val, t, serializer, err);
    }
}

#endif // JSON_TUPLE_H
