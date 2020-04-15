#ifndef XMLVALUE_H
#define XMLVALUE_H

#include <FDXml/XmlAttribute.h>
#include <FDXml/Xml_allocator.h>

#include <rapidxml/rapidxml.hpp>

#include <string>

namespace FDXml
{
    class XmlValue
    {
        protected:
            rapidxml::xml_node<> *m_node;

        public:
            XmlValue();

            XmlValue(rapidxml::xml_node<> *node);

            XmlValue(const std::string_view name);

            XmlValue(const std::string_view name,
                     const std::string_view value);

            operator bool() const { return m_node != nullptr; }

            rapidxml::xml_node<> *get() { return m_node; }
            const rapidxml::xml_node<> *get() const { return m_node; }

            rapidxml::xml_node<> *operator->() { return m_node; }
            const rapidxml::xml_node<> *operator->() const { return m_node; }

            XmlValue getChildNode(const std::string_view name);

            const XmlValue getChildNode(const std::string_view name) const;

            void addChildNode(XmlValue &value);

            void removeChildNode(XmlValue &value);

            void clearChildNodes();

            XmlValue operator[](const std::string_view name)
            {
                return getChildNode(name);
            }

            XmlValue operator[](const std::string_view name) const
            {
                return getChildNode(name);
            }

            XmlAttribute getAttribute(const std::string_view name);

            const XmlAttribute getAttribute(const std::string_view name) const;

            XmlAttribute operator()(const std::string_view name)
            {
                return getAttribute(name);
            }

            const XmlAttribute operator()(const std::string_view name) const
            {
                return getAttribute(name);
            }

            void setAttribute(const std::string_view name, const std::string_view value);

            void setAttribute(XmlAttribute attr);

            void removeAttribute(const std::string_view &name);

            bool hasAttribute(const std::string_view &name) const;

            void clearAttributes();

            void clear();

            bool isNull() const;

            bool isChar() const;

            bool isString() const;

            bool isInt() const;

            bool isUInt() const;

            bool isFloat() const;

            bool isNumber() const;

            bool isBool() const;

            bool isArray() const;

            bool isObject() const;
    };
}

#endif // XMLVALUE_H
