#include <FDXml/XmlSerializer.h>

#include <FDCore/FileUtils.h>

#include <cstring>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <rapidxml/rapidxml_print.hpp>
#pragma GCC diagnostic pop

#include <fstream>
#include <sstream>

#include <memory>


void FDXml::XmlSerializerImpl::clearMemory()
{
    m_doc.clear();
}

bool FDXml::XmlSerializerImpl::parseFile(const std::string_view path, std::string *err)
{
    std::unique_ptr<char[]> text(FDCore::readFile(path.data()).release());

    LastError= { nullptr, nullptr };
    rapidxml::xml_document<> doc;
    doc.parse<0>(text.get());
    if(LastError.first != nullptr)
    {
        if(err)
        {
            *err += LastError.first;
            *err += ": '";
            *err += reinterpret_cast<char*>(LastError.second);
            *err += "'";
        }

        return false;
    }

    return true;
}

bool FDXml::XmlSerializerImpl::parseString(const std::string_view str, std::string *err)
{
    std::unique_ptr<char[]> text(FDCore::readFile(str.data()).release());
    memcpy(text.get(), str.data(), str.size() + 1);

    LastError= { nullptr, nullptr };
    rapidxml::xml_document<> doc;
    doc.parse<0>(text.get());
    if(LastError.first != nullptr)
    {
        if(err)
        {
            *err += LastError.first;
            *err += ": '";
            *err += reinterpret_cast<char*>(LastError.second);
            *err += "'";
        }

        return false;
    }

    return true;
}

std::string FDXml::XmlSerializerImpl::print(const FDXml::XmlSerializerImpl::Value &val)
{
    std::ostringstream oss;
    oss << *val;
    return oss.str();
}

void FDXml::XmlSerializerImpl::save(const FDXml::XmlSerializerImpl::Value &val, const std::string_view path)
{
    std::ofstream file(path.data());
    file << *val;
}
