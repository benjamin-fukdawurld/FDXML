#ifndef FDXML_TEST_SET_H
#define FDXML_TEST_SET_H

#include <gtest/gtest.h>

#include <FDXml/XmlSerializer.h>
#include <FDXml/Xml_set.h>

TEST(TestXmlSet, TestSerializeSet)
{
    FDXml::Serializer serializer;
    {
        const std::unordered_set<int> s = {0, 1, 2, 3};
        FDXml::Serializer::Value val = serializer.serialize(s);

        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), s.size());
        std::string err;
        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            int i;
            ASSERT_TRUE(it->isInt());
            ASSERT_TRUE(serializer.unserialize(*it, i, &err)) << err;
            ASSERT_TRUE(s.find(i) != s.end());
        }

    }

    {
        const std::set<std::string> s = {"faubaf", "azfaezf", "000000", ""};
        FDXml::Serializer::Value val = serializer.serialize(s);

        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), s.size());
        for(auto it = val.begin(), end = val.end(); it != end; ++it)
        {
            ASSERT_TRUE(it->isString());
            ASSERT_TRUE(s.find(std::string(it->getAttribute("value").getValue())) != s.end());
        }
    }
}

TEST(TestXmlSet, TestUnserializeSet)
{
    FDXml::Serializer serializer;
    {
        const std::unordered_set<int> in = {0, 1, 2, 3};
        FDXml::Serializer::Value val = serializer.serialize(in);
        std::unordered_set<int> s;
        std::string err;

        ASSERT_TRUE(serializer.unserialize(val, s, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            ASSERT_TRUE(s.find(i) != s.end());
        }
    }

    {
        const std::set<std::string> in = {"faubaf", "azfaezf", "000000", ""};
        FDXml::Serializer::Value val = serializer.serialize(in);
        std::unordered_set<std::string> s;
        std::string err;

        ASSERT_TRUE(serializer.unserialize(val, s, &err)) << err;
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            ASSERT_TRUE(s.find(*it) != s.end());
        }
    }
}

#endif // FDXML_TEST_SET_H
