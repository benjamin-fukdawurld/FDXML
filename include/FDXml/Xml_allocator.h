#ifndef XML_ALLOCATOR_H
#define XML_ALLOCATOR_H

#include <rapidxml/rapidxml.hpp>

namespace FDXml
{
    struct Xml_helper
    {
        static rapidxml::memory_pool<> allocator;
    };
}

#endif // XML_ALLOCATOR_H
