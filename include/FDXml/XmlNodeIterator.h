#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include <iterator>

#include <FDXml/XmlValue.h>

#include <map>

namespace FDXml
{
    namespace internal
    {
        template<typename Derived>
        class XmlNodeIteratorTrait :
                public std::iterator<std::bidirectional_iterator_tag, XmlValue, size_t, XmlValue*, XmlValue&>
        {
            protected:
                const XmlValue *m_parent;
                mutable XmlValue m_node;

            public:
                XmlNodeIteratorTrait()
                {}

                explicit XmlNodeIteratorTrait(const XmlValue &parent, XmlValue node):
                    m_parent(&parent),
                    m_node(node)
                {}

                XmlNodeIteratorTrait(const XmlNodeIteratorTrait &) = default;
                XmlNodeIteratorTrait(XmlNodeIteratorTrait&&) = default;

                XmlNodeIteratorTrait &operator=(const XmlNodeIteratorTrait &) = default;
                XmlNodeIteratorTrait &operator=(XmlNodeIteratorTrait&&) = default;

                virtual ~XmlNodeIteratorTrait() = default;

                bool operator==(const Derived &other)
                {
                    return m_parent == other.m_parent && m_node.get() == other.m_node.get();
                }

                bool operator!=(const Derived &other) { return !(*this == other); }

                XmlValue &operator*() { return m_node; }
                const XmlValue &operator*() const { return m_node; }

                XmlValue *operator->() { return &m_node; }
                const XmlValue *operator->() const { return &m_node; }
        };
    }

    class XmlNodeIterator : public internal::XmlNodeIteratorTrait<XmlNodeIterator>
    {
        public:
            using internal::XmlNodeIteratorTrait<XmlNodeIterator>::XmlNodeIteratorTrait;

            XmlNodeIterator &operator++();
            const XmlNodeIterator &operator++() const;

            XmlNodeIterator operator++(int);
            const XmlNodeIterator operator++(int) const;

            XmlNodeIterator &operator--();
            const XmlNodeIterator &operator--() const;

            XmlNodeIterator operator--(int);
            const XmlNodeIterator operator--(int) const;
    };

    class XmlNodeReverseIterator : public internal::XmlNodeIteratorTrait<XmlNodeReverseIterator>
    {
        public:
            using internal::XmlNodeIteratorTrait<XmlNodeReverseIterator>::XmlNodeIteratorTrait;

            XmlNodeReverseIterator &operator++();
            const XmlNodeReverseIterator &operator++() const;

            XmlNodeReverseIterator operator++(int);
            const XmlNodeReverseIterator operator++(int) const;

            XmlNodeReverseIterator &operator--();
            const XmlNodeReverseIterator &operator--() const;

            XmlNodeReverseIterator operator--(int);
            const XmlNodeReverseIterator operator--(int) const;
    };
}

#endif // NODEITERATOR_H
