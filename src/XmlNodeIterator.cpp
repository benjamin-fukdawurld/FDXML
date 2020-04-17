#include <FDXml/XmlNodeIterator.h>

FDXml::XmlNodeIterator &FDXml::XmlNodeIterator::operator++()
{
    m_node = m_node->next_sibling();
    return *this;
}

const FDXml::XmlNodeIterator &FDXml::XmlNodeIterator::operator++() const
{
    m_node = m_node->next_sibling();
    return *this;
}

FDXml::XmlNodeIterator FDXml::XmlNodeIterator::operator++(int)
{
    XmlNodeIterator result(*this);
    m_node = m_node->next_sibling();
    return result;
}

const FDXml::XmlNodeIterator FDXml::XmlNodeIterator::operator++(int) const
{
    const XmlNodeIterator result(*this);
    m_node = m_node->next_sibling();
    return result;
}

FDXml::XmlNodeIterator FDXml::XmlNodeIterator::operator--(int)
{
    XmlNodeIterator result(*this);
    if(m_node)
        m_node = m_node->previous_sibling();
    else
        m_node = m_parent->get()->last_node();

    return result;
}

const FDXml::XmlNodeIterator FDXml::XmlNodeIterator::operator--(int) const
{
    const XmlNodeIterator result(*this);
    if(m_node)
        m_node = m_node->previous_sibling();
    else
        m_node = m_parent->get()->last_node();

    return result;
}

const FDXml::XmlNodeIterator &FDXml::XmlNodeIterator::operator--() const
{
    if(m_node)
        m_node = m_node->previous_sibling();
    else
        m_node = m_parent->get()->last_node();

    return *this;
}

FDXml::XmlNodeIterator &FDXml::XmlNodeIterator::operator--()
{
    if(m_node)
        m_node = m_node->previous_sibling();
    else
        m_node = m_parent->get()->last_node();

    return *this;
}

FDXml::XmlNodeReverseIterator &FDXml::XmlNodeReverseIterator::operator++()
{
    m_node = m_node->previous_sibling();
    return *this;
}

const FDXml::XmlNodeReverseIterator &FDXml::XmlNodeReverseIterator::operator++() const
{
    m_node = m_node->previous_sibling();
    return *this;
}

FDXml::XmlNodeReverseIterator FDXml::XmlNodeReverseIterator::operator++(int)
{
    XmlNodeReverseIterator result(*this);
    m_node = m_node->previous_sibling();
    return result;
}

const FDXml::XmlNodeReverseIterator FDXml::XmlNodeReverseIterator::operator++(int) const
{
    const XmlNodeReverseIterator result(*this);
    m_node = m_node->previous_sibling();
    return result;
}

FDXml::XmlNodeReverseIterator FDXml::XmlNodeReverseIterator::operator--(int)
{
    XmlNodeReverseIterator result(*this);
    if(m_node)
        m_node = m_node->next_sibling();
    else
        m_node = m_parent->get()->first_node();

    return result;
}

const FDXml::XmlNodeReverseIterator FDXml::XmlNodeReverseIterator::operator--(int) const
{
    const XmlNodeReverseIterator result(*this);
    if(m_node)
        m_node = m_node->next_sibling();
    else
        m_node = m_parent->get()->first_node();

    return result;
}

const FDXml::XmlNodeReverseIterator &FDXml::XmlNodeReverseIterator::operator--() const
{
    if(m_node)
        m_node = m_node->next_sibling();
    else
        m_node = m_parent->get()->first_node();

    return *this;
}

FDXml::XmlNodeReverseIterator &FDXml::XmlNodeReverseIterator::operator--()
{
    if(m_node)
        m_node = m_node->next_sibling();
    else
        m_node = m_parent->get()->first_node();

    return *this;
}
