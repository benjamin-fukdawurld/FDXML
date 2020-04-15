#include <FDXml/XmlValue.h>

#include <FDXml/Xml_allocator.h>

#include <algorithm>

FDXml::XmlValue::XmlValue(rapidxml::xml_node<> *node):
    m_node(node)
{

}

FDXml::XmlValue::XmlValue():
    m_node(nullptr)
{
}

FDXml::XmlValue::XmlValue(const std::string_view name)
{
    m_node = FDXml::Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                        Xml_helper::allocator.allocate_string(name.data(), name.size()), nullptr, name.size(), 0);
}

FDXml::XmlValue::XmlValue(const std::string_view name, const std::string_view value)
{
    m_node = FDXml::Xml_helper::allocator.allocate_node(rapidxml::node_element,
                                                        Xml_helper::allocator.allocate_string(name.data(), name.size()),
                                                        Xml_helper::allocator.allocate_string(name.data(), name.size()),
                                                        name.size(), value.size());
}

FDXml::XmlValue FDXml::XmlValue::getChildNode(const std::string_view name)
{
    assert(m_node != nullptr);
    return m_node->first_node(name.data(), name.size());
}

void FDXml::XmlValue::addChildNode(FDXml::XmlValue &value)
{
    assert(m_node != nullptr);
    m_node->append_node(value.get());
}

void FDXml::XmlValue::removeChildNode(FDXml::XmlValue &value)
{
    assert(m_node != nullptr);
    m_node->remove_node(value.get());
}

void FDXml::XmlValue::clearChildNodes()
{
    assert(m_node != nullptr);
    m_node->remove_all_nodes();
}

FDXml::XmlAttribute FDXml::XmlValue::getAttribute(const std::string_view name)
{
    assert(m_node != nullptr);
    return m_node->first_attribute(name.data(), name.size());
}

const FDXml::XmlAttribute FDXml::XmlValue::getAttribute(const std::string_view name) const
{
    assert(m_node != nullptr);
    return m_node->first_attribute(name.data(), name.size());
}

void FDXml::XmlValue::setAttribute(const std::string_view name, const std::string_view value)
{
    assert(m_node != nullptr);
    XmlAttribute attr = m_node->first_attribute(name.data(), name.size());
    if(attr)
        attr->value(Xml_helper::allocator.allocate_string(value.data(), value.size()), value.size());
    else
    {
        m_node->append_attribute(Xml_helper::allocator.allocate_attribute(
                                     Xml_helper::allocator.allocate_string(name.data(), name.size()),
                                     Xml_helper::allocator.allocate_string(value.data(), value.size()),
                                     name.size(), value.size()));
    }
}

void FDXml::XmlValue::setAttribute(FDXml::XmlAttribute attr)
{
    assert(m_node != nullptr);
    std::string_view name = attr.getName();
    XmlAttribute current = m_node->first_attribute(name.data(), name.size());
    if(current)
        m_node->remove_attribute(current.get());

    m_node->append_attribute(attr.get());
}

void FDXml::XmlValue::removeAttribute(const std::string_view &name)
{
    assert(m_node != nullptr);
    m_node->remove_attribute(getAttribute(name).get());
}

bool FDXml::XmlValue::hasAttribute(const std::string_view &name) const
{
    assert(m_node != nullptr);
    return m_node->first_attribute(name.data(), name.size()) != nullptr;
}

void FDXml::XmlValue::clearAttributes()
{
    assert(m_node != nullptr);
    m_node->remove_all_attributes();
}

void FDXml::XmlValue::clear()
{
    assert(m_node != nullptr);
    m_node->remove_all_attributes();
    m_node->remove_all_nodes();
}

bool FDXml::XmlValue::isNull() const
{
    assert(m_node != nullptr);
    const XmlAttribute attr = getAttribute("value");
    return !attr || attr->value_size() == 0;
}

bool FDXml::XmlValue::isChar() const
{
    assert(m_node != nullptr);
    return std::string("char") == m_node->name();
}

bool FDXml::XmlValue::isString() const
{
    assert(m_node != nullptr);
    return std::string("str") == m_node->name();
}

bool FDXml::XmlValue::isInt() const
{
    assert(m_node != nullptr);
    return std::string("int") == m_node->name();
}

bool FDXml::XmlValue::isUInt() const
{
    if(!isInt())
        return false;

    std::string_view str = getAttribute("value").getValue();
    return std::find(str.begin(), str.end(), '-') == str.end();
}

bool FDXml::XmlValue::isFloat() const
{
    assert(m_node != nullptr);
    return std::string("float") == m_node->name();
}

bool FDXml::XmlValue::isNumber() const
{
    return isInt() || isFloat();
}

bool FDXml::XmlValue::isBool() const
{
    assert(m_node != nullptr);
    return std::string("bool") == m_node->name();
}

bool FDXml::XmlValue::isArray() const
{
    assert(m_node != nullptr);
    return std::string("array") == m_node->name();
}

bool FDXml::XmlValue::isObject() const
{
    assert(m_node != nullptr);
    return std::string("object") == m_node->name();
}
