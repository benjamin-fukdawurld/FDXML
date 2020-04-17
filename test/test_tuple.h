#ifndef FDXML_TEST_TUPLE_H
#define FDXML_TEST_TUPLE_H


#include <gtest/gtest.h>

#include <FDXml/Xml_tuple_fwd.h>

#include <FDXml/Xml_primitive.h>
#include <FDXml/Xml_tuple.h>
#include <FDXml/XmlSerializer.h>

TEST(TestXmlTuple, TestSerializeTuple)
{
    {
        std::tuple<int, float, std::string> t = std::make_tuple(1, 3.14f, "test");
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(t);
        ASSERT_TRUE(val.isArray());
        ASSERT_EQ(val.size(), 3u);
        EXPECT_TRUE(val[0ul].isInt());
        EXPECT_EQ(val[0ul].getAttribute("value").getValue(), std::to_string(std::get<0>(t)));
        EXPECT_TRUE(val[1].isFloat());
        EXPECT_EQ(val[1].getAttribute("value").getValue(), std::to_string(std::get<1>(t)));
        EXPECT_TRUE(val[2].isString());
        EXPECT_EQ(val[2].getAttribute("value").getValue(), std::get<2>(t));
    }
}

TEST(TestXmlTuple, TestSerializePair)
{
    {
        std::pair<int, std::string> p = std::make_pair(1, "test");
        FDXml::Serializer::Value val = FDXml::Serializer::getInstance().serialize(p);
        ASSERT_TRUE(val.isObject());
        ASSERT_TRUE(val.hasChildNode("first"));
        EXPECT_TRUE(val["first"].isInt());
        EXPECT_EQ(val["first"].getValue(), std::to_string(p.first));
        ASSERT_TRUE(val.hasChildNode("second"));
        EXPECT_TRUE(val["second"].isString());
        EXPECT_EQ(val["second"].getValue(), p.second);
    }
}

TEST(TestXmlTuple, TestUnserializePair)
{
    {
        std::pair<int, std::string> in = std::make_pair(1, "test");
        std::pair<int, std::string> t;
        FDXml::XmlValue val("pair");
        val.addChildNode({ "first", "int", std::to_string(in.first) });
        val.addChildNode({ "second", "str", in.second });
        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, &err)) << err;
        EXPECT_EQ(t.first, in.first);
        EXPECT_EQ(t.second, in.second);
    }
}

TEST(TestXmlTuple, TestUnserializeTuple)
{
    {
        std::tuple<int, float, std::string> in = std::make_tuple(1, 3.14f, "test");
        std::tuple<int, float, std::string> t;
        FDXml::Serializer::Value val("array");
        val.addChildNode(FDXml::Serializer::getInstance().serialize(std::get<0>(in)));
        val.addChildNode(FDXml::Serializer::getInstance().serialize(std::get<1>(in)));
        val.addChildNode(FDXml::Serializer::getInstance().serialize(std::get<2>(in)));
        std::string err;
        ASSERT_TRUE(FDXml::Serializer::getInstance().unserialize(val, t, &err)) << err;
        EXPECT_EQ(std::get<0>(t), std::get<0>(in));
        EXPECT_EQ(std::get<1>(t), std::get<1>(in));
        EXPECT_EQ(std::get<2>(t), std::get<2>(in));
    }
}

#endif // FDXML_TEST_TUPLE_H
