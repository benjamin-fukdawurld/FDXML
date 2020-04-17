#include "include/FDXml/XmlAttributeIterator.h"

#include <FDXml/XmlValue.h>

FDXml::XmlAttributeIterator &FDXml::XmlAttributeIterator::operator++()
{
    m_attr = m_attr->next_attribute();
    return *this;
}

const FDXml::XmlAttributeIterator &FDXml::XmlAttributeIterator::operator++() const
{
    m_attr = m_attr->next_attribute();
    return *this;
}

FDXml::XmlAttributeIterator FDXml::XmlAttributeIterator::operator++(int)
{
    FDXml::XmlAttributeIterator result(*this);
    m_attr = m_attr->next_attribute();
    return result;
}

const FDXml::XmlAttributeIterator FDXml::XmlAttributeIterator::operator++(int) const
{
    const FDXml::XmlAttributeIterator result(*this);
    m_attr = m_attr->next_attribute();
    return result;
}

FDXml::XmlAttributeIterator &FDXml::XmlAttributeIterator::operator--()
{
    if(m_attr)
        m_attr = m_attr->next_attribute();
    else
        m_attr = m_node->get()->last_attribute();

    return *this;
}

const FDXml::XmlAttributeIterator &FDXml::XmlAttributeIterator::operator--() const
{
    if(m_attr)
        m_attr = m_attr->next_attribute();
    else
        m_attr = m_node->get()->last_attribute();

    return *this;
}

FDXml::XmlAttributeIterator FDXml::XmlAttributeIterator::operator--(int)
{
    FDXml::XmlAttributeIterator result(*this);
    if(m_attr)
        m_attr = m_attr->next_attribute();
    else
        m_attr = m_node->get()->last_attribute();

    return result;
}

const FDXml::XmlAttributeIterator FDXml::XmlAttributeIterator::operator--(int) const
{
    const FDXml::XmlAttributeIterator result(*this);
    if(m_attr)
        m_attr = m_attr->next_attribute();
    else
        m_attr = m_node->get()->last_attribute();

    return result;
}


FDXml::XmlAttributeReverseIterator &FDXml::XmlAttributeReverseIterator::operator++()
{
    m_attr = m_attr->previous_attribute();
    return *this;
}

const FDXml::XmlAttributeReverseIterator &FDXml::XmlAttributeReverseIterator::operator++() const
{
    m_attr = m_attr->previous_attribute();
    return *this;
}

FDXml::XmlAttributeReverseIterator FDXml::XmlAttributeReverseIterator::operator++(int)
{
    FDXml::XmlAttributeReverseIterator result(*this);
    m_attr = m_attr->previous_attribute();
    return result;
}

const FDXml::XmlAttributeReverseIterator FDXml::XmlAttributeReverseIterator::operator++(int) const
{
    const FDXml::XmlAttributeReverseIterator result(*this);
    m_attr = m_attr->previous_attribute();
    return result;
}

FDXml::XmlAttributeReverseIterator &FDXml::XmlAttributeReverseIterator::operator--()
{
    if(m_attr)
        m_attr = m_attr->previous_attribute();
    else
        m_attr = m_node->get()->first_attribute();

    return *this;
}

const FDXml::XmlAttributeReverseIterator &FDXml::XmlAttributeReverseIterator::operator--() const
{
    if(m_attr)
        m_attr = m_attr->previous_attribute();
    else
        m_attr = m_node->get()->first_attribute();

    return *this;
}

FDXml::XmlAttributeReverseIterator FDXml::XmlAttributeReverseIterator::operator--(int)
{
    FDXml::XmlAttributeReverseIterator result(*this);
    if(m_attr)
        m_attr = m_attr->previous_attribute();
    else
        m_attr = m_node->get()->first_attribute();

    return result;
}

const FDXml::XmlAttributeReverseIterator FDXml::XmlAttributeReverseIterator::operator--(int) const
{
    const FDXml::XmlAttributeReverseIterator result(*this);
    if(m_attr)
        m_attr = m_attr->previous_attribute();
    else
        m_attr = m_node->get()->first_attribute();

    return result;
}
