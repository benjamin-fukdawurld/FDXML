#ifndef XMLATTRIBUTEITERATOR_H
#define XMLATTRIBUTEITERATOR_H

#include <FDXml/XmlAttribute.h>
#include <iterator>

namespace FDXml
{
    class XmlValue;
    namespace internal
    {
        template<typename Derived>
        class XmlAttributeIteratorTrait :
                public std::iterator<std::bidirectional_iterator_tag, XmlValue, size_t, XmlValue*, XmlValue&>
        {
            protected:
                const XmlValue *m_node;
                mutable XmlAttribute m_attr;

            public:
                XmlAttributeIteratorTrait()
                {}

                virtual ~XmlAttributeIteratorTrait() = default;

                explicit XmlAttributeIteratorTrait(const XmlValue &node, XmlAttribute attr):
                    m_node(&node),
                    m_attr(attr)
                {}

                bool operator==(const Derived &other)
                {
                    return m_node == m_node && m_attr.get() == other.m_attr.get();
                }

                bool operator!=(const Derived &other) { return !(*this == other); }

                XmlAttribute &operator*() { return m_attr; }
                const XmlAttribute &operator*() const { return m_attr; }

                XmlAttribute &operator->() { return m_attr; }
                const XmlAttribute &operator->() const { return m_attr; }
        };
    }

    class XmlAttributeIterator : public internal::XmlAttributeIteratorTrait<XmlAttributeIterator>
    {
        public:
            using internal::XmlAttributeIteratorTrait<XmlAttributeIterator>::XmlAttributeIteratorTrait;

            XmlAttributeIterator &operator++();
            const XmlAttributeIterator &operator++() const;

            XmlAttributeIterator operator++(int);
            const XmlAttributeIterator operator++(int) const;

            XmlAttributeIterator &operator--();
            const XmlAttributeIterator &operator--() const;

            XmlAttributeIterator operator--(int);
            const XmlAttributeIterator operator--(int) const;
    };

    class XmlAttributeReverseIterator : public internal::XmlAttributeIteratorTrait<XmlAttributeReverseIterator>
    {
        public:
            using internal::XmlAttributeIteratorTrait<XmlAttributeReverseIterator>::XmlAttributeIteratorTrait;

            XmlAttributeReverseIterator &operator++();
            const XmlAttributeReverseIterator &operator++() const;

            XmlAttributeReverseIterator operator++(int);
            const XmlAttributeReverseIterator operator++(int) const;

            XmlAttributeReverseIterator &operator--();
            const XmlAttributeReverseIterator &operator--() const;

            XmlAttributeReverseIterator operator--(int);
            const XmlAttributeReverseIterator operator--(int) const;
    };
}

#endif // XMLATTRIBUTEITERATOR_H
