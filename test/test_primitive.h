#ifndef FDXML_TEST_PRIMITIVE_H
#define FDXML_TEST_PRIMITIVE_H

#include <gtest/gtest.h>

#include <FDXml/Xml_primitive_fwd.h>
#include <FDXml/XmlSerializer.h>
#include <FDXml/Xml_primitive.h>

TEST(TestXmlPrimitive, TestSerializeText)
{
    FDXml::Serializer serializer;
    { // Char
        char c = 'A';
        FDXml::Serializer::Value val = serializer.serialize(c);
        FDXml::XmlAttribute attr(val->first_attribute("value", 5), serializer);
        ASSERT_TRUE(val);
        ASSERT_TRUE(attr);
        EXPECT_EQ(attr->name_size(), 5u);
        EXPECT_STREQ(attr->name(), "value");
        EXPECT_EQ(attr->value_size(), 1u);
        EXPECT_STREQ(attr->value(), "A");
    }

    { // C String
        const char *cstr = "this is a text string";
        size_t len = strlen(cstr);
        FDXml::Serializer::Value val = serializer.serialize(cstr);
        FDXml::XmlAttribute attr(val->first_attribute("value", 5), serializer);
        ASSERT_TRUE(val);
        ASSERT_TRUE(attr);
        EXPECT_EQ(attr->name_size(), 5u);
        EXPECT_STREQ(attr->name(), "value");
        EXPECT_EQ(attr->value_size(), len);
        EXPECT_STREQ(attr->value(), cstr);
    }

    { // String
        std::string str = "this is a text string";
        FDXml::Serializer::Value val = serializer.serialize(str);
        FDXml::XmlAttribute attr(val->first_attribute("value", 5), serializer);
        ASSERT_TRUE(val);
        ASSERT_TRUE(attr);
        EXPECT_EQ(attr->name_size(), 5u);
        EXPECT_STREQ(attr->name(), "value");
        EXPECT_EQ(attr->value_size(), str.size());
        EXPECT_STREQ(attr->value(), str.c_str());
    }
}

TEST(TestXmlPrimitive, TestUnserializeText)
{
    FDXml::Serializer serializer;
    { // Char
        char c = '\0';
        FDXml::XmlValue val("char", serializer);
        val.setAttribute("value", "A");
        std::string err;
        ASSERT_TRUE(val.isChar()) << val.getNodeType();
        ASSERT_TRUE(serializer.unserialize(val, c, &err)) << err;
        ASSERT_EQ('A', c);
    }

    { // String
        const char *in = "test string";
        std::string str;
        FDXml::Serializer::Value val("str", serializer);
        val.setAttribute("value", in);
        std::string err;
        ASSERT_TRUE(val.isString());
        ASSERT_TRUE(serializer.unserialize(val, str, &err)) << err;
        ASSERT_EQ(strlen(in), str.size());
        ASSERT_STREQ(in, str.c_str());
    }
}

TEST(TestXmlPrimitive, TestSerializeBoolean)
{
    FDXml::Serializer serializer;
    bool b = true;
    FDXml::Serializer::Value val = serializer.serialize(b);
    FDXml::XmlAttribute attr(val.getAttribute("value"));
    ASSERT_STREQ(attr->value(), "true");
}

TEST(TestXmlPrimitive, TestUnserializeBoolean)
{
    FDXml::Serializer serializer;
    bool b = false;
    FDXml::Serializer::Value val("bool", serializer);
    val.setAttribute("value", "true");
    std::string err;
    ASSERT_TRUE(val.isBool());
    ASSERT_TRUE(serializer.unserialize(val, b, &err)) << err;
    ASSERT_TRUE(b);
}

TEST(TestXmlPrimitive, TestSerializeInteger)
{
    FDXml::Serializer serializer;
    { // Int 16 & Uint 16
        {
            int16_t i = -1564;
            FDXml::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.isInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(i));
        }

        {
            uint16_t u = 26116u;
            FDXml::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.isUInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(u));
        }
    }

    { // Int 32 & Uint 32
        {
            int32_t i = 6496461;
            FDXml::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.isInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(i));
        }

        {
            uint32_t u = 646486432u;
            FDXml::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.isUInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(u));
        }
    }

    { // Int 64 & Uint 64
        {
            int64_t i = 56148646;
            FDXml::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.isInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(i));
        }

        {
            uint64_t u = 54646131564u;
            FDXml::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.isUInt());
            EXPECT_EQ(val.getAttribute("value").getValue(), std::to_string(u));
        }
    }
}

TEST(TestXmlPrimitive, TestUnserializeInteger)
{
    FDXml::Serializer serializer;
    { // Int 16 & Uint 16
        {
            int16_t i;
            FDXml::Serializer::Value val("int", "int", "-1564", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(-1564, i);
        }

        {
            uint16_t u;
            FDXml::Serializer::Value val("int", "int", "26116", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(26116u, u);
        }
    }

    { // Int 32 & Uint 32
        {
            int32_t i;
            FDXml::Serializer::Value val("int", "int", "6496461", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(6496461, i);
        }

        {
            uint32_t u;
            FDXml::Serializer::Value val("int", "int", "646486432", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(646486432u, u);
        }
    }

    { // Int 64 & Uint 64
        {
            int64_t i;
            FDXml::Serializer::Value val("int", "int", "56148646", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(56148646, i);
        }

        {
            uint64_t u;
            FDXml::Serializer::Value val("int", "int", "54646131564", serializer);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(54646131564u, u);
        }
    }
}

TEST(TestXmlPrimitive, TestSerializeNull)
{
    FDXml::Serializer serializer;
    FDXml::Serializer::Value val = serializer.serialize(nullptr);
    ASSERT_TRUE(val.isNull());
}

TEST(TestXmlPrimitive, TestUnserializeNull)
{
    FDXml::Serializer serializer;
    std::optional<bool> b;
    FDXml::Serializer::Value val("bool", serializer);
    std::string err;
    ASSERT_TRUE(serializer.unserialize(val, b, &err)) << err;
    ASSERT_FALSE(b.has_value());
}

#endif // FDXML_TEST_PRIMITIVE_H
