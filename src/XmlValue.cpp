#include <FDXml/XmlValue.h>

#include <FDXml/XmlSerializer.h>

#include <algorithm>

static bool isObjectType(const std::string_view type)
{
    static const std::array<const std::string_view, 6> types = {
        "bool",
        "char",
        "int",
        "float",
        "str",
        "array"
    };

    return std::find(types.begin(), types.end(), type.data()) == types.end();
}

FDXml::XmlValue::XmlValue(rapidxml::xml_node<> *node):
    m_node(node)
{}

FDXml::XmlValue::XmlValue():
    m_node(nullptr)
{}

FDXml::XmlValue::XmlValue(const std::string_view name):
    XmlValue(name, name)
{}

FDXml::XmlValue::XmlValue(const std::string_view name, const std::string_view type):
    XmlValue(name, type, nullptr)
{}

FDXml::XmlValue::XmlValue(const std::string_view name, const std::string_view type, const std::string_view value)
{
    m_node = FDXml::Serializer::getInstance().getAllocator().allocate_node(rapidxml::node_element,
                                                        FDXml::Serializer::getInstance().getAllocator().allocate_string(name.data(), name.size() + 1),
                                                        nullptr, name.size(), 0);

    if(type.data() == nullptr)
        setAttribute("node-data-type", "undefined");
    else
    {
        if(!isObjectType(type))
            setAttribute("node-data-type", type);
        else
        {
            setAttribute("node-data-type", "object");
            setAttribute("node-object-type", type);
        }
    }

    if(value.data() != nullptr)
        setAttribute("value", value);

    if(isArray())
        setAttribute("size", "0");
}

FDXml::XmlValue::iterator FDXml::XmlValue::begin()
{
    return XmlNodeIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::iterator FDXml::XmlValue::end()
{
    return XmlNodeIterator(*this, XmlValue());
}

FDXml::XmlValue::const_iterator FDXml::XmlValue::begin() const
{
    return XmlNodeIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::const_iterator FDXml::XmlValue::end() const
{
    return XmlNodeIterator(*this, XmlValue());
}

FDXml::XmlValue::const_iterator FDXml::XmlValue::cbegin() const
{
    return XmlNodeIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::const_iterator FDXml::XmlValue::cend() const
{
    return XmlNodeIterator(*this, XmlValue());
}

FDXml::XmlValue::reverse_iterator FDXml::XmlValue::rbegin()
{
    return XmlNodeReverseIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::reverse_iterator FDXml::XmlValue::rend()
{
    return XmlNodeReverseIterator(*this, XmlValue());
}

FDXml::XmlValue::const_reverse_iterator FDXml::XmlValue::rbegin() const
{
    return XmlNodeReverseIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::const_reverse_iterator FDXml::XmlValue::rend() const
{
    return XmlNodeReverseIterator(*this, XmlValue());
}

FDXml::XmlValue::const_reverse_iterator FDXml::XmlValue::crbegin() const
{
    return XmlNodeReverseIterator(*this, XmlValue(m_node->first_node()));
}

FDXml::XmlValue::const_reverse_iterator FDXml::XmlValue::crend() const
{
    return XmlNodeReverseIterator(*this, XmlValue());
}

FDXml::XmlValue::attribute_iterator FDXml::XmlValue::attribute_begin()
{
    return XmlAttributeIterator(*this, XmlAttribute(m_node->first_attribute()));
}

FDXml::XmlValue::attribute_iterator FDXml::XmlValue::attribute_end()
{
    return XmlAttributeIterator(*this, XmlAttribute());
}

FDXml::XmlValue::const_attribute_iterator FDXml::XmlValue::attribute_begin() const
{
    return XmlAttributeIterator(*this, XmlAttribute(m_node->first_attribute()));
}

FDXml::XmlValue::const_attribute_iterator FDXml::XmlValue::attribute_end() const
{
    return XmlAttributeIterator(*this, XmlAttribute());
}

FDXml::XmlValue::const_attribute_iterator FDXml::XmlValue::attribute_cbegin() const
{
    return XmlAttributeIterator(*this, XmlAttribute(m_node->first_attribute()));
}

FDXml::XmlValue::const_attribute_iterator FDXml::XmlValue::attribute_cend() const
{
    return XmlAttributeIterator(*this, XmlAttribute());
}

FDXml::XmlValue::reverse_attribute_iterator FDXml::XmlValue::attribute_rbegin()
{
    return XmlAttributeReverseIterator(*this, XmlAttribute(m_node->last_attribute()));
}

FDXml::XmlValue::reverse_attribute_iterator FDXml::XmlValue::attribute_rend()
{
    return XmlAttributeReverseIterator(*this, XmlAttribute());
}

FDXml::XmlValue::const_reverse_attribute_iterator FDXml::XmlValue::attribute_rbegin() const
{
    return XmlAttributeReverseIterator(*this, XmlAttribute(m_node->last_attribute()));
}

FDXml::XmlValue::const_reverse_attribute_iterator FDXml::XmlValue::attribute_rend() const
{
    return XmlAttributeReverseIterator(*this, XmlAttribute());
}

FDXml::XmlValue::const_reverse_attribute_iterator FDXml::XmlValue::attribute_crbegin() const
{
    return XmlAttributeReverseIterator(*this, XmlAttribute(m_node->last_attribute()));
}

FDXml::XmlValue::const_reverse_attribute_iterator FDXml::XmlValue::attribute_crend() const
{
    return XmlAttributeReverseIterator(*this, XmlAttribute());
}

FDXml::XmlValue FDXml::XmlValue::getChildNode(const std::string_view name)
{
    assert(m_node != nullptr);
    return m_node->first_node(name.data(), name.size());
}

const FDXml::XmlValue FDXml::XmlValue::getChildNode(const std::string_view name) const
{
    assert(m_node != nullptr);
    return m_node->first_node(name.data(), name.size());
}


void FDXml::XmlValue::addChildNode(FDXml::XmlValue value)
{
    assert(m_node != nullptr);
    m_node->append_node(value.get());
    if(isArray())
    {
        size_t s = 0;
        s = std::stoul(getAttribute("size").getValue().data()) + 1;
        setAttribute("size", std::to_string(s));
    }
}

void FDXml::XmlValue::removeChildNode(FDXml::XmlValue value)
{
    assert(m_node != nullptr);
    m_node->remove_node(value.get());
}

void FDXml::XmlValue::clearChildNodes()
{
    assert(m_node != nullptr);
    m_node->remove_all_nodes();
}

const FDXml::XmlValue FDXml::XmlValue::operator[](const char *name) const
{
    return getChildNode(name);
}

FDXml::XmlValue FDXml::XmlValue::operator[](const char *name)
{
    return getChildNode(name);
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
        attr.setValue(value);
    else
    {
        m_node->append_attribute(XmlAttribute(name, value).get());
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

bool FDXml::XmlValue::hasChildren() const
{
    assert(m_node != nullptr);
    return m_node->first_node() != nullptr;
}

bool FDXml::XmlValue::hasAttribute() const
{
    assert(m_node != nullptr);
    return m_node->first_attribute() != nullptr;
}

bool FDXml::XmlValue::hasAttribute(const std::string_view &name) const
{
    assert(m_node != nullptr);
    return m_node->first_attribute(name.data(), name.size()) != nullptr;
}

bool FDXml::XmlValue::hasChildNode(const std::string_view &name) const
{
    assert(m_node != nullptr);
    return m_node->first_node(name.data()) != nullptr;
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

std::string_view FDXml::XmlValue::getName() const
{
    return m_node->name();
}

void FDXml::XmlValue::setName(std::string_view name)
{
    return m_node->name(FDXml::Serializer::getInstance().getAllocator().allocate_string(name.data(), name.size() + 1));
}

std::string_view FDXml::XmlValue::getValue() const
{
    const XmlAttribute attr = getAttribute("value");
    return attr ? attr.getValue() : nullptr;
}

std::string_view FDXml::XmlValue::getNodeType() const
{
    const XmlAttribute attr = getAttribute("node-data-type");
    return attr ? attr.getValue() : "undefined";
}

std::string_view FDXml::XmlValue::getObjectType() const
{
    const XmlAttribute attr = getAttribute("node-object-type");
    return attr ? attr.getValue() : "undefined";
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
    return getNodeType() == "char";
}

bool FDXml::XmlValue::isString() const
{
    assert(m_node != nullptr);
    return getNodeType() == std::string("str");
}

bool FDXml::XmlValue::isInt() const
{
    assert(m_node != nullptr);
    return getNodeType() == std::string("int");
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
    return getNodeType() == std::string("float");
}

bool FDXml::XmlValue::isNumber() const
{
    return isInt() || isFloat();
}

bool FDXml::XmlValue::isBool() const
{
    assert(m_node != nullptr);
    return getNodeType() == std::string("bool");
}

bool FDXml::XmlValue::isArray() const
{
    assert(m_node != nullptr);
    return getNodeType() == std::string("array");
}

bool FDXml::XmlValue::isObject() const
{
    assert(m_node != nullptr);
    return getNodeType() == std::string("object");
}

size_t FDXml::XmlValue::size() const
{
    assert(m_node != nullptr);
    if(!isArray())
        return 1;

    size_t s = 0;
    s = std::stoul(getAttribute("size").getValue().data());

    return s;
}

FDXml::XmlValue FDXml::XmlValue::operator[](size_t pos)
{
    assert(m_node != nullptr);
    assert(isArray());
    rapidxml::xml_node<> *n = m_node->first_node();
    for(size_t i = 0; i < pos && n != nullptr; ++i)
        n = n->next_sibling();

    return FDXml::XmlValue(n);
}

const FDXml::XmlValue FDXml::XmlValue::operator[](size_t pos) const
{
    assert(m_node != nullptr);
    assert(isArray());
    rapidxml::xml_node<> *n = m_node->first_node();
    for(size_t i = 0; i < pos && n != nullptr; ++i)
        n = n->next_sibling();

    return FDXml::XmlValue(n);
}
