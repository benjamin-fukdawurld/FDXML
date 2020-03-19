#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FDXml
TEMPLATE = lib
CONFIG += console c++17
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

LIBS += -Lbuild/lib -lFDSerialize

DEPENDPATH += include \
    ../FDSerialize/include \
    ../thirdparty/rapidxml/include

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../thirdparty/

SOURCES += \
    src/Xml_utils.cpp

HEADERS += \
    include/FDXml/FDXml.h \
    include/FDXml/Xml_allocator.h \
    include/FDXml/Xml_array.h \
    include/FDXml/Xml_array_fwd.h \
    include/FDXml/Xml_fwd.h \
    include/FDXml/Xml_list.h \
    include/FDXml/Xml_list_fwd.h \
    include/FDXml/Xml_map.h \
    include/FDXml/Xml_map_fwd.h \
    include/FDXml/Xml_primitive.h \
    include/FDXml/Xml_primitive_fwd.h \
    include/FDXml/Xml_set.h \
    include/FDXml/Xml_set_fwd.h \
    include/FDXml/Xml_utils.h \
    include/FDXml/XmlSerializer.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
