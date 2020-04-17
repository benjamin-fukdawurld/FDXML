#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <FDSerialize/SerializerBase.h>

#include <FDXml/Xml_fwd.h>
#include <FDXml/XmlValue.h>

namespace FDXml
{
    class XmlSerializerImpl
    {
        friend class FDSerialize::SerializerBase<XmlSerializerImpl>;
        public:
            typedef rapidxml::xml_document<> Document;
            typedef rapidxml::memory_pool<> Allocator;
            typedef XmlValue Value;

        protected:
            Document m_doc;

        private:
            XmlSerializerImpl() = default;
            XmlSerializerImpl(XmlSerializerImpl&&) = delete;
            XmlSerializerImpl(const XmlSerializerImpl&) = delete;

            XmlSerializerImpl &operator=(XmlSerializerImpl&&) = delete;
            XmlSerializerImpl &operator=(const XmlSerializerImpl&) = delete;

        public:
            void clearMemory();

            const Document &getCurrentDocument() const
            {
                return m_doc;
            }

            Allocator &getAllocator()
            {
                return m_doc;
            }

            bool parseFile(const std::string_view path, std::string *err = nullptr);

            bool parseString(const std::string_view str, std::string *err = nullptr);

            std::string print(const Value &val);

            void save(const Value &val, const std::string_view path);

            template<typename T>
            Value serialize(T &&obj, Serializer &serializer)
            {
                return FDXml::serialize(std::forward<T>(obj), serializer);
            }

            template<typename T>
            Value serialize(const T &obj, Serializer &serializer)
            {
                return FDXml::serialize(obj, serializer);
            }

            template<typename T>
            Value serialize(T obj[], size_t len, Serializer &serializer)
            {
                return FDXml::serialize(obj, len, serializer);
            }

            template<typename T>
            bool unserialize(const Value &val, T &out, Serializer &serializer, std::string *err = nullptr)
            {
                return FDXml::unserialize(val, out, serializer, err);
            }

            template<typename T>
            bool unserialize(const Value &val, T out[], size_t len, Serializer &serializer, std::string *err = nullptr)
            {
                return FDXml::unserialize(val, out, len, serializer, err);
            }

            static std::pair<const char*, void*> LastError;
    };
}

#endif // XMLSERIALIZER_H
