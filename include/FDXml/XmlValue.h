#ifndef XMLVALUE_H
#define XMLVALUE_H

#include <FDXml/XmlAttribute.h>

#include <FDXml/FDXml.h>

#include <string>

namespace FDXml
{
    class XmlNodeIterator;
    class XmlAttributeIterator;
    class XmlNodeReverseIterator;
    class XmlAttributeReverseIterator;

    class XmlValue
    {
        public:
            typedef XmlNodeIterator iterator;
            typedef const XmlNodeIterator const_iterator;
            typedef XmlNodeReverseIterator reverse_iterator;
            typedef const XmlNodeReverseIterator const_reverse_iterator;

            typedef XmlAttributeIterator attribute_iterator;
            typedef const XmlAttributeIterator const_attribute_iterator;
            typedef XmlAttributeReverseIterator reverse_attribute_iterator;
            typedef const XmlAttributeReverseIterator const_reverse_attribute_iterator;

        protected:
            rapidxml::xml_node<> *m_node;

        public:
            XmlValue();

            XmlValue(rapidxml::xml_node<> *node);

            XmlValue(const std::string_view name);

            XmlValue(const std::string_view name,
                     const std::string_view type);

            XmlValue(const std::string_view name,
                     const std::string_view type,
                     const std::string_view value);

            operator bool() const { return m_node != nullptr; }

            rapidxml::xml_node<> &operator*() { return *m_node; }
            const rapidxml::xml_node<> &operator*() const { return *m_node; }

            rapidxml::xml_node<> *get() { return m_node; }
            const rapidxml::xml_node<> *get() const { return m_node; }

            rapidxml::xml_node<> *operator->() { return m_node; }
            const rapidxml::xml_node<> *operator->() const { return m_node; }

            iterator begin();
            iterator end();

            const_iterator begin() const;
            const_iterator end() const;

            const_iterator cbegin() const;
            const_iterator cend() const;

            reverse_iterator rbegin();
            reverse_iterator rend();

            const_reverse_iterator rbegin() const;
            const_reverse_iterator rend() const;

            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;

            attribute_iterator attribute_begin();
            attribute_iterator attribute_end();

            const_attribute_iterator attribute_begin() const;
            const_attribute_iterator attribute_end() const;

            const_attribute_iterator attribute_cbegin() const;
            const_attribute_iterator attribute_cend() const;

            reverse_attribute_iterator attribute_rbegin();
            reverse_attribute_iterator attribute_rend();

            const_reverse_attribute_iterator attribute_rbegin() const;
            const_reverse_attribute_iterator attribute_rend() const;

            const_reverse_attribute_iterator attribute_crbegin() const;
            const_reverse_attribute_iterator attribute_crend() const;

            XmlValue getChildNode(const std::string_view name);

            const XmlValue getChildNode(const std::string_view name) const;

            void addChildNode(XmlValue value);

            void removeChildNode(XmlValue value);

            void clearChildNodes();

            XmlValue operator[](const char *name);

            const XmlValue operator[](const char *name) const;

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


            bool hasChildren() const;
            bool hasAttribute() const;

            bool hasChildNode(const std::string_view &name) const;
            bool hasAttribute(const std::string_view &name) const;

            void clearAttributes();

            void clear();

            std::string_view getName() const;
            void setName(std::string_view name);

            std::string_view getValue() const;

            std::string_view getNodeType() const;
            std::string_view getObjectType() const;

            bool isUndefined() const;

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

            size_t size() const;

            XmlValue operator[](size_t pos);
            const XmlValue operator[](size_t pos) const;
    };
}

#endif // XMLVALUE_H

#include <FDXml/XmlNodeIterator.h>
#include <FDXml/XmlAttributeIterator.h>
