#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <rapidxml/rapidxml.hpp>

#include <FDXml/Xml_allocator.h>

#include <string>

namespace FDXml
{
    class XmlAttribute
    {
        protected:
            rapidxml::xml_attribute<> *m_attr;

        public:
            XmlAttribute();

            XmlAttribute(rapidxml::xml_attribute<> *attr);

            XmlAttribute(const std::string_view name);

            XmlAttribute(const std::string_view name,
                         const std::string_view value);

            operator bool() const { return m_attr != nullptr; }

            rapidxml::xml_attribute<> *get() { return m_attr; }
            const rapidxml::xml_attribute<> *get() const { return m_attr; }

            rapidxml::xml_attribute<> *operator->() { return m_attr; }
            const rapidxml::xml_attribute<> *operator->() const { return m_attr; }

            std::string_view getName() const;

            void setName(const std::string_view str);

            std::string_view getValue() const;

            void setValue(const std::string_view str);
    };
}

#endif // XMLATTRIBUTE_H
