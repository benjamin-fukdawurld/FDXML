#include "include/FDXml/XmlAttribute.h"

FDXml::XmlAttribute::XmlAttribute() :
    m_attr(nullptr)
{}


FDXml::XmlAttribute::XmlAttribute(const std::string_view name):
    m_attr(FDXml::Xml_helper::allocator.allocate_attribute(FDXml::Xml_helper::allocator.allocate_string(name.data(), name.size()), nullptr, name.size(), 0))
{}

FDXml::XmlAttribute::XmlAttribute(rapidxml::xml_attribute<> *attr) :
    m_attr(attr)
{}


FDXml::XmlAttribute::XmlAttribute(const std::string_view name, const std::string_view value):
    m_attr(FDXml::Xml_helper::allocator.allocate_attribute(FDXml::Xml_helper::allocator.allocate_string(name.data(), name.size()),
                                                           FDXml::Xml_helper::allocator.allocate_string(value.data(), value.size()),
                                                           name.size(), value.size()))
{}

std::string_view FDXml::XmlAttribute::getName() const
{
    assert(m_attr != nullptr);
    return std::string_view(m_attr->name(), m_attr->name_size());
}


void FDXml::XmlAttribute::setName(const std::string_view str)
{
    assert(m_attr != nullptr);
    m_attr->name(FDXml::Xml_helper::allocator.allocate_string(str.data(), str.size()), str.size());
}

std::string_view FDXml::XmlAttribute::getValue() const
{
    assert(m_attr != nullptr);
    return std::string_view(m_attr->value(), m_attr->value_size());
}

void FDXml::XmlAttribute::setValue(const std::string_view str)
{
    assert(m_attr != nullptr);
    m_attr->value(FDXml::Xml_helper::allocator.allocate_string(str.data(), str.size()), str.size());
}
