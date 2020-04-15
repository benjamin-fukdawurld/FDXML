#include <FDXml/Xml_utils.h>

rapidxml::memory_pool<> FDXml::Xml_helper::allocator;

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, std::nullptr_t)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name), nullptr);
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const char c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(std::string(1, c).c_str()));
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, char &c, std::string *err)
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

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const char *c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c));
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, std::string &&c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c.c_str()));
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const std::string &c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c.c_str()));
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, std::string &c, std::string *)
{
    c = attr->value();
    return true;
}

FDXml::XmlAttribute FDXml::serialize_attribute(const char *name, const bool b)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(b ? "true" : "false"));
}

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, bool &c, std::string *err)
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

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, int64_t &i, std::string *err)
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

bool FDXml::unserialize_attribute(const FDXml::XmlAttribute &attr, uint64_t &i, std::string *err)
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


FDXml::XmlValue FDXml::serialize(const char c)
{
    FDXml::XmlValue result("char");
    result.setAttribute(serialize_attribute("value", c));
    return result;
}

FDXml::XmlValue FDXml::serialize(const char *c)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", c));
    return result;
}

FDXml::XmlValue FDXml::serialize(std::string &&c)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", c));
    return result;
}

FDXml::XmlValue FDXml::serialize(const std::string &c)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", c));
    return result;
}

FDXml::XmlValue FDXml::serialize(const bool b)
{
    FDXml::XmlValue result("str");
    result.setAttribute(serialize_attribute("value", b));
    return result;
}
