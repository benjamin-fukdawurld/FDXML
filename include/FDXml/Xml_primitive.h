#ifndef XML_PRIMITIVE_H
#define XML_PRIMITIVE_H

#include <FDXml/Xml_primitive_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, T &&i, Serializer &)
    {
        return XmlAttribute(name, std::to_string(std::move(i)));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlAttribute> serialize_attribute(const char *name, const T &i, Serializer &)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value
                || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &i, Serializer &tag, std::string *err)
    {
        int64_t result = 0;
        if(!FDXml::unserialize_attribute(attr, result, tag, err))
            return false;

        if(result > std::numeric_limits<T>::max() || result < std::numeric_limits<T>::min())
        {
            if(err)
                *err = "Attribute value is out of range";

            return false;
        }

        i = static_cast<T>(result);
        return true;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute> serialize_attribute(const char *name, T &&i, Serializer &)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute> serialize_attribute(const char *name, const T &i, Serializer &)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value || std::is_same<T, double>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &f, Serializer &, std::string *err)
    {
        std::string val = attr->value();
        size_t pos = 0;
        long double result = std::stold(val, &pos);
        if(pos != val.size())
        {
            if(err)
                *err = "Attribute is not a floating pount number";

            return false;
        }

        if(result > static_cast<long double>(std::numeric_limits<T>::max())
           || result < static_cast<long double>(std::numeric_limits<T>::min()))
        {
            if(err)
                *err = "Attribute value is out of range";

            return false;
        }

        f = static_cast<T>(result);

        return true;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidxml::xml_node<> *> serialize(T &&i, Serializer &tag)
    {
        XmlValue result("int");
        result.setAttribute(serialize_attribute("value", std::move(i), tag));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlValue> serialize(const T &i, Serializer &tag)
    {
        XmlValue result("int");
        result.setAttribute(serialize_attribute("value", i, tag));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue> serialize(T &&i, Serializer &tag)
    {
        XmlValue result("float");
        result.setAttribute(serialize_attribute("value", i, tag));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue> serialize(const T &i, Serializer &tag)
    {
        XmlValue result("float");
        result.setAttribute(serialize_attribute("value", i, tag));
        return result;
    }

    template<typename T>
    bool unserialize_attribute(const XmlAttribute &attr, std::optional<T> &opt, Serializer &tag, std::string *err)
    {
        if(!attr || attr->value_size() == 0)
        {
            opt = std::nullopt;
            return true;
        }

        return unserialize(attr, opt.value(), tag, err);
    }

    template<typename T>
    bool unserialize(const XmlValue &val, std::optional<T> &opt, Serializer &tag, std::string *err)
    {
        if(val.isNull())
        {
            opt = std::nullopt;
            return true;
        }

        return unserialize<T>(val, opt.value(), tag, err);
    }

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
                        || std::is_same<T, float>::value
                        || std::is_same<T, double>::value,
    bool> unserialize(const XmlValue &val, T &v, Serializer &tag, std::string *err)
    {
        const XmlAttribute &attr = val.getAttribute("value");

        if(!attr)
        {
            if(err)
                *err = "Node has no 'value' attribute";

            return false;
        }

        if(!unserialize_attribute(attr, v, tag, err))
        {
            if(err)
                *err = std::string("Node's attribute 'value':") + *err;

            return false;
        }

        return true;
    }
}

#endif // XML_PRIMITIVE_H
