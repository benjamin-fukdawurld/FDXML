#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <FDXml/FDXml.h>

#include <string>

namespace FDXml
{
    class XmlAttribute
    {
        public:
            typedef rapidxml::memory_pool<> Allocator;

        protected:
            rapidxml::xml_attribute<> *m_attr;
            Serializer &m_serializer;

        public:
            XmlAttribute(Serializer &serializer);

            XmlAttribute(rapidxml::xml_attribute<> *attr,
                         Serializer &serializer);

            XmlAttribute(const std::string_view name,
                         Serializer &serializer);

            XmlAttribute(const std::string_view name,
                         const std::string_view value,
                         Serializer &serializer);

            XmlAttribute &operator=(rapidxml::xml_attribute<> *a)
            {
                m_attr = a;
                return *this;
            }

            Serializer &getSerializer() { return m_serializer; }
            const Serializer &getSerializer() const { return m_serializer; }

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
