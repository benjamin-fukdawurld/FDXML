#include <FDXml/XmlAttribute.h>

#include <FDXml/XmlSerializer.h>

FDXml::XmlAttribute::XmlAttribute(Serializer &serializer) :
    XmlAttribute(nullptr, serializer)
{}

FDXml::XmlAttribute::XmlAttribute(rapidxml::xml_attribute<> *attr, Serializer &serializer) :
    m_attr(attr),
    m_serializer(serializer)
{}

FDXml::XmlAttribute::XmlAttribute(const std::string_view name,
                                  Serializer &serializer):
    XmlAttribute(serializer.getAllocator().allocate_attribute(serializer.getAllocator().allocate_string(name.data(), name.size() + 1),
                 nullptr, name.size(), 0), serializer)
{}

FDXml::XmlAttribute::XmlAttribute(const std::string_view name, const std::string_view value, Serializer &serializer):
    XmlAttribute(serializer.getAllocator().allocate_attribute(serializer.getAllocator().allocate_string(name.data(), name.size() + 1),
                 serializer.getAllocator().allocate_string(value.data(), value.size() + 1), name.size(), value.size()), serializer)
{}

std::string_view FDXml::XmlAttribute::getName() const
{
    assert(m_attr != nullptr);
    return std::string_view(m_attr->name(), m_attr->name_size());
}


void FDXml::XmlAttribute::setName(const std::string_view str)
{
    assert(m_attr != nullptr);
    m_attr->name(m_serializer.getAllocator().allocate_string(str.data(), str.size() + 1), str.size());
}

std::string_view FDXml::XmlAttribute::getValue() const
{
    assert(m_attr != nullptr);
    return std::string_view(m_attr->value(), m_attr->value_size());
}

void FDXml::XmlAttribute::setValue(const std::string_view str)
{
    assert(m_attr != nullptr);
    m_attr->value(m_serializer.getAllocator().allocate_string(str.data(), str.size() + 1), str.size());
}
