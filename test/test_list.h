#ifndef FDXML_TEST_LIST_H
#define FDXML_TEST_LIST_H

#include <gtest/gtest.h>

#include <FDXml/Xml_primitive.h>
#include <FDXml/Xml_list.h>
#include <FDXml/XmlSerializer.h>

TEST(TestXmlList, TestSerializeList)
{
    FDXml::Serializer serializer;
    { // std::vector of int
        std::list<int> l = {0, 1, 2, 3};
        FDXml::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 4u);
        auto it = l.begin();
        for(size_t i = 0, i_max = 4; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].isInt());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), std::to_string(*it));
        }
    }

    { // std::deque of string
        std::forward_list<std::string> l = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDXml::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 6u);
        auto it = l.begin();
        for(size_t i = 0, i_max = 6; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].isString());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), *it);
        }
    }
}

TEST(TestXmlList, TestUnserializeList)
{
    FDXml::Serializer serializer;
    { // std::vector of int
        std::list<int> l;
        FDXml::Serializer::Value val = serializer.serialize(std::initializer_list<int>{0, 1, 2, 3});
        std::string err;
        ASSERT_TRUE(serializer.unserialize(val, l, &err)) << err;
        ASSERT_EQ(l.size(), 4u);
        auto it = l.begin();
        for(size_t i = 0, i_max = 4; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].isInt());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), std::to_string(*it));
        }
    }

    { // std::deque of string
        std::forward_list<std::string> l = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDXml::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 6u);
        auto it = l.begin();
        for(size_t i = 0, i_max = 6; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].isString());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), *it);
        }
    }
}

#endif // FDXML_TEST_LIST_H
