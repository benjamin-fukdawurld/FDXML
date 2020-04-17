#include <FDXml/Xml_utils.h>

#include <FDXml/XmlSerializer.h>

std::pair<const char*, void*> FDXml::XmlSerializerImpl::LastError;

void rapidxml::parse_error_handler(const char *what, void *where)
{
    FDXml::XmlSerializerImpl::LastError = std::make_pair(what, where);
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, std::nullptr_t, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name);
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const char c, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name, std::string(1, c));
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, char &c, Serializer &, std::string *err)
{
    if(attr->value_size() != 1)
    {
        if(err)
            *err = "Attribute is not a char";

        return false;
    }

    c = attr->value()[0];
    return true;
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const char *c, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name, c);
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, std::string &&c, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name, c);
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const std::string &c, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name, c);
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, std::string &c, Serializer &, std::string *)
{
    c = attr->value();
    return true;
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const bool b, Serializer &)
{
    assert("Attribute must have a name" && name != nullptr);
    return FDXml::XmlAttribute(name, b ? "true" : "false");
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, bool &c, Serializer &, std::string *err)
{
    std::string val = attr->value();
    if(val == "true")
        c = true;
    else if(val == "false")
        c = false;
    else
    {
        if(err)
            *err = "Attribute is not a bool";

        return false;
    }

    return true;
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, int64_t &i, Serializer &, std::string *err)
{
    std::string val = attr->value();
    size_t pos = 0;
    int64_t result = std::stoll(val, &pos);
    if(pos != val.size())
    {
        if(err)
            *err = "Attribute is not an integer";

        return false;
    }

    i = result;

    return true;
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, uint64_t &i, Serializer &, std::string *err)
{
    std::string val = attr->value();
    size_t pos = 0;
    uint64_t result = std::stoull(val, &pos);
    if(pos != val.size())
    {
        if(err)
            *err = "Attribute is not an unsingned integer";

        return false;
    }

    i = result;

    return true;
}


FDXml::XmlValue FDXml::serialize(const char c, Serializer &tag)
{
    FDXml::XmlValue result("char");
    result.setAttribute(serialize_attribute("value", c, tag));
    return result;
}

FDXml::XmlValue FDXml::serialize(const char *c, Serializer &tag)
{
    FDXml::XmlValue result("str");

    if(c != nullptr)
        result.setAttribute(serialize_attribute("value", c, tag));
    else
        result.setAttribute(serialize_attribute("value", nullptr, tag));

    return result;
}

FDXml::XmlValue FDXml::serialize(std::string &&c, Serializer &tag)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", c, tag));
    return result;
}

FDXml::XmlValue FDXml::serialize(const std::string &c, Serializer &tag)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", c, tag));
    return result;
}

FDXml::XmlValue FDXml::serialize(const bool b, Serializer &tag)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", b, tag));
    return result;
}
