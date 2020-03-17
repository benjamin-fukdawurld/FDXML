#include <FDXml/Xml_utils.h>

rapidxml::memory_pool<> FDXml::Xml_helper::allocator;

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, std::nullptr_t)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name), nullptr);
}

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, const char c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(std::string(1, c).c_str()));
}

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, const char *c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c));
}

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, std::string &&c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c.c_str()));
}

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, const std::string &c)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(c.c_str()));
}

rapidxml::xml_attribute<> *FDXml::serialize_attribute(const char *name, const bool b)
{
    return Xml_helper::allocator.allocate_attribute(Xml_helper::allocator.allocate_string(name),
                                                    Xml_helper::allocator.allocate_string(b ? "true" : "false"));
}


rapidxml::xml_node<> *FDXml::serialize(const char c)
{
    rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "char");
    result->append_attribute(serialize_attribute("value", c));
    return result;
}

rapidxml::xml_node<> *FDXml::serialize(const char *c)
{
    rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "str");
    result->append_attribute(serialize_attribute("value", c));
    return result;
}

rapidxml::xml_node<> *FDXml::serialize(std::string &&c)
{
    rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "str");
    result->append_attribute(serialize_attribute("value", c));
    return result;
}

rapidxml::xml_node<> *FDXml::serialize(const std::string &c)
{
    rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "str");
    result->append_attribute(serialize_attribute("value", c));
    return result;
}

rapidxml::xml_node<> *FDXml::serialize(const bool b)
{
    rapidxml::xml_node<> *result = Xml_helper::allocator.allocate_node(rapidxml::node_element, "bool");
    result->append_attribute(serialize_attribute("value", b));
    return result;
}
