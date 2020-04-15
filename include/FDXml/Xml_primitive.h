#ifndef XML_PRIMITIVE_H
#define XML_PRIMITIVE_H

#include <FDXml/XmlValue.h>
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
    XmlAttribute> serialize_attribute(const char *name, T &&i)
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
    XmlAttribute> serialize_attribute(const char *name, const T &i)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value
                || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, T &i, std::string *err)
    {
        int64_t result = 0;
        if(!FDXml::unserialize_attribute(attr, result, err))
            return false;

        if(result > std::numeric_limits<T>::max() || result > std::numeric_limits<T>::min())
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
    XmlAttribute> serialize_attribute(const std::string_view name, T &&i)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlAttribute> serialize_attribute(const std::string_view name, const T &i)
    {
        return XmlAttribute(name, std::to_string(i));
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value || std::is_same<T, double>::value,
    bool> unserialize_attribute(const XmlAttribute &attr, float &f, std::string *err)
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
           || result < static_cast<long double>(std::numeric_limits<T>::max()))
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
    rapidxml::xml_node<> *> serialize(T &&i)
    {
        XmlValue result("int");
        result.setAttribute(serialize_attribute("value", std::move(i)));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    XmlValue> serialize(const T &i)
    {
        XmlValue result("int");
        result.setAttribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue> serialize(T &&i)
    {
        XmlValue result("float");
        result.setAttribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, float>::value
                  || std::is_same<T, double>::value,
    XmlValue> serialize(const T &i)
    {
        XmlValue result("float");
        result.setAttribute(serialize_attribute("value", i));
        return result;
    }

    template<typename T>
    bool unserialize_attribute(const XmlAttribute &attr, std::optional<T> &opt, std::string *err)
    {
        if(!attr || attr->value_size() == 0)
        {
            opt = std::nullopt;
            return true;
        }

        return unserialize(attr, opt.value(), err);
    }

    template<typename T>
    bool unserialize(const XmlValue &val, std::optional<T> &opt, std::string *err)
    {
        if(val.isNull())
        {
            opt = std::nullopt;
            return true;
        }

        return unserialize<T>(val, opt.value(), err);
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
                        ||std::is_same<T, float>::value
                        || std::is_same<T, double>::value,
    bool> unserialize(const XmlValue &val, T &v, std::string *err)
    {
        const XmlAttribute &attr = val.getAttribute("value");

        if(!attr || attr->value_size() == 0)
        {
            if(err)
                *err = "Node has no 'value' attribute";

            return false;
        }

        if(!unserialize_attribute(attr, v, err))
        {
            if(err)
                *err = std::string("Node's attribute 'value':") + *err;

            return false;
        }

        return true;
    }
}

#endif // XML_PRIMITIVE_H
