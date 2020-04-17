#ifndef FDXML_TEST_ARRAY_H
#define FDXML_TEST_ARRAY_H

#include <gtest/gtest.h>

#include <FDXml/Xml_primitive.h>
#include <FDXml/Xml_array.h>
#include <FDXml/XmlSerializer.h>

TEST(TestXmlArray, TestSerializeStaticArray)
{
    { // int[]
        int t[4] = {0, 1, 2, 3};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(t, 4);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 4u);
        for(size_t i = 0, i_max = 4; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].isInt());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), std::to_string(t[i]));
        }
    }

    { // std::array of string
        std::array<std::string, 6> t = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(t);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 6u);
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].isString());
            EXPECT_EQ(val[i].getAttribute("value").getValue(), t[i]);
        }
    }
}

TEST(TestXmlArray, TestUnserializeStaticArray)
{
    { // int[]
        int t[4];
        FDXml::Serializer::Value val("array");
        val.setAttribute("size", "4");
        val->append_node(FDXml::XmlValue("int", "int", "0").get());
        val->append_node(FDXml::XmlValue("int", "int", "1").get());
        val->append_node(FDXml::XmlValue("int", "int", "2").get());
        val->append_node(FDXml::XmlValue("int", "int", "3").get());
        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, 4, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], i);
        }
    }

    { // std::array of string
        const std::array<std::string, 6> in = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        std::array<std::string, 6> t;
        FDXml::Serializer::Value val("array");
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
            val.addChildNode(FDXml::Serializer::Value("str", "str", in[i]));

        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], in[i]);
        }
    }
}


TEST(TestXmlArray, TestSerializeDynamicArray)
{
    { // std::vector of int
        std::vector<int> v = {0, 1, 2, 3};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(v);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 4u);
        size_t i = 0;
        for(auto it = val.cbegin(); it != val.cend(); ++it, ++i)
        {
            ASSERT_TRUE(it->isInt());
            EXPECT_EQ(it->getAttribute("value").getValue(), std::to_string(v[i]));
        }
    }

    { // std::deque of string
        std::deque<std::string> d = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(d);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 6u);
        size_t i = 0;
        for(auto it = val.cbegin(); it != val.cend(); ++it, ++i)
        {
            ASSERT_TRUE(it->isString());
            EXPECT_EQ(it->getAttribute("value").getValue(), d[i]);
        }
    }
}

TEST(TestXmlArray, TestUnserializeDynamicArray)
{
    { // std::vector of int
        int t[4];
        FDXml::Serializer::Value val("array");
        val.addChildNode({"int", "int", "0"});
        val.addChildNode({"int", "int", "1"});
        val.addChildNode({"int", "int", "2"});
        val.addChildNode({"int", "int", "3"});
        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, 4, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], i);
        }
    }

    { // std::deque of string
        const std::array<std::string, 6> in = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        std::deque<std::string> t;
        FDXml::Serializer::Value val("array");
        val.addChildNode({"str", "str", in[0]});
        val.addChildNode({"str", "str", in[1]});
        val.addChildNode({"str", "str", in[2]});
        val.addChildNode({"str", "str", in[3]});
        val.addChildNode({"str", "str", in[4]});
        val.addChildNode({"str", "str", in[5]});

        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], in[i]);
        }
    }
}

#endif // FDXML_TEST_ARRAY_H
