#ifndef FDXML_TEST_MAP_H
#define FDXML_TEST_MAP_H

#include <gtest/gtest.h>

#include <FDXml/Xml_fwd.h>
#include <FDXml/XmlSerializer.h>

TEST(TestXmlMap, TestSerializeMap)
{
    {
        std::map<int, int> m = {{0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0}};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(m);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), m.size());
        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            ASSERT_TRUE(it->isObject());
            ASSERT_TRUE(it->hasChildNode("key"));
            ASSERT_TRUE(it->hasChildNode("value"));
            ASSERT_TRUE((*it)["key"].isInt());
            ASSERT_TRUE((*it)["value"].isInt());
            auto key_it = m.find(std::stoi(std::string((*it)["key"].getValue())));
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(std::to_string(key_it->second), (*it)["value"].getValue());
        }
    }

    /*{
        std::map<std::string, int> m = {{"fezgve", 4}, {"vzseg", 3}, {"fzsgfrze", 2}, {"3zbverza", 1}};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(m);
        ASSERT_TRUE(val.isObject());
        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            ASSERT_TRUE(it->isInt());
            auto key_it = m.find(std::string(it->getName()));
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(std::to_string(key_it->second), it->getValue());
        }
    }*/
}

/*TEST(TestXmlMap, TestUnserializeMap)
{
    {
        const std::map<int, int> in = {{0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0}};
        std::map<int, int> m;
        FDXml::Serializer::Value val("array");
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            FDXml::Serializer::Value cell(map);
            cell.AddMember("key", FDXml::Serializer::Value(it->first), FDXml::FDJson::Serializer::getInstance().getAllocator());
            cell.AddMember("value", FDXml::Serializer::Value(it->second), FDXml::FDJson::Serializer::getInstance().getAllocator());
            val.PushBack(cell, FDXml::FDJson::Serializer::getInstance().getAllocator());
        }

        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, m, &err));
        ASSERT_EQ(in.size(), m.size());
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            auto key_it = m.find(it->first);
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, it->second);
        }
    }

    {
        const std::map<std::string, int> in = {{"fezgve", 4}, {"vzseg", 3}, {"fzsgfrze", 2}, {"3zbverza", 1}};
        std::map<std::string, int> m;
        FDXml::Serializer::Value val(map);
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            val.AddMember(FDXml::Serializer::Value(it->first.c_str(), FDXml::FDJson::Serializer::getInstance().getAllocator()),
                          FDXml::Serializer::Value(it->second), FDXml::FDJson::Serializer::getInstance().getAllocator());
        }
        std::string err;

        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, m, &err));
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            auto key_it = m.find(it->first);
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, it->second);
        }
    }
}*/

#endif // FDXML_TEST_MAP_H
