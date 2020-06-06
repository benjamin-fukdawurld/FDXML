#ifndef FDXML_TEST_CUSTOM_H
#define FDXML_TEST_CUSTOM_H

#include <gtest/gtest.h>

#include <FDXml/FDXml.h>
#include <FDXml/Xml_fwd.h>
#include <FDXml/XmlValue.h>

struct TestClass
{
    int i;
    float f;
    char c;
    std::string str;

    TestClass(int i = 42, float f = 3.14f, char c = 'A', const std::string &str = "toto"):
        i(i), f(f), c(c), str(str)
    {}
};

namespace FDXml
{
    XmlValue serialize(TestClass &&c, FDXml::Serializer &serializer);

    XmlValue serialize(const TestClass &c);

    bool unserialize(const XmlValue &val, TestClass &str, std::string *err = nullptr);
}


#include <FDXml/Xml_utils.h>
#include <FDXml/XmlSerializer.h>

namespace FDXml
{
    XmlValue serialize(TestClass &&c, Serializer &serializer)
    {
        XmlValue val("TestClass", serializer);

        XmlValue i = FDXml::serialize(c.i, serializer);
        i.setName("i");
        val.addChildNode(i);

        XmlValue f = FDXml::serialize(c.f, serializer);
        f.setName("f");
        val.addChildNode(f);

        XmlValue ch = FDXml::serialize(c.c, serializer);
        ch.setName("c");
        val.addChildNode(ch);

        XmlValue str = FDXml::serialize(c.str, serializer);
        str.setName("str");
        val.addChildNode(str);
        return val;
    }

    XmlValue serialize(const TestClass &c, Serializer &serializer)
    {
        XmlValue val("TestClass", serializer);

        XmlValue i = FDXml::serialize(c.i, serializer);
        i.setName("i");
        val.addChildNode(i);

        XmlValue f = FDXml::serialize(c.f, serializer);
        f.setName("f");
        val.addChildNode(f);

        XmlValue ch = FDXml::serialize(c.c, serializer);
        ch.setName("c");
        val.addChildNode(ch);

        XmlValue str = FDXml::serialize(c.str, serializer);
        str.setName("str");
        val.addChildNode(str);
        return val;
    }

    bool unserialize(const XmlValue &val, TestClass &c, Serializer &tag, std::string *err)
    {
        if(!val.isObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        if(val.getObjectType() != "TestClass")
        {
            if(err)
                *err = "Value is not an TestClass";

            return false;
        }

        return FDXml::unserialize(val["i"], c.i, tag, err)
                && FDXml::unserialize(val["f"], c.f, tag, err)
                && FDXml::unserialize(val["c"], c.c, tag, err)
                && FDXml::unserialize(val["str"], c.str, tag, err);
    }
}

#include <FDCore/FileUtils.h>
#include <fstream>
#include <cstdio>

TEST(TestJsonCustom, TestSerializeCustomType)
{
    FDXml::Serializer serializer;
    std::ofstream file("TestClass.xml");
    FDXml::XmlValue val = FDXml::serialize(TestClass(), serializer);
    ASSERT_EQ(val["i"].getValue(), "42");
    ASSERT_EQ(val["f"].getValue(), std::to_string(3.14f));
    ASSERT_EQ(val["c"].getValue(), "A");
    ASSERT_EQ(val["str"].getValue(), "toto");

    serializer.save(val, "TestClass.xml");
}

TEST(TestJsonCustom, TestUnserializeReflectConfig)
{
    FDXml::Serializer serializer;
    std::unique_ptr<char[]> text = FDCore::readFile("TestClass.xml");

    rapidxml::xml_document<> doc;    // character type defaults to char
    doc.parse<0>(text.get());
    FDXml::XmlValue val(doc.first_node(), serializer);

    TestClass c;
    std::string err;
    ASSERT_TRUE(FDXml::unserialize(val, c, serializer, &err)) << err;
    ASSERT_EQ(c.i, 42);
    ASSERT_FLOAT_EQ(c.f, 3.14f);
    ASSERT_EQ(c.c, 'A');
    ASSERT_EQ(c.str, "toto");
}


#endif // FDXML_TEST_CUSTOM_H
