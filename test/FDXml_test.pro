TARGET = FDXml_test

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../../build/bin
MAKEFILE = ../../build/makefiles/$${TARGET}
OBJECTS_DIR = ../../build/.obj/$${TARGET}

LIBS += \
    -pthread \
    -L../../build/lib -lFDXml \
    -L../../thirdparty/googletest/build/lib -lgtest

INCLUDEPATH += \
    ../../FDSerialize/include \
    ../../FDXml/include \
    ../../thirdparty/rapidxml/include \
    ../../thirdparty/googletest/googletest/include \

SOURCES += \
    main.cpp

HEADERS += \
    test_custom.h \
    test_primitive.h \
    test_array.h \
    test_list.h \
    test_tuple.h \
    test_set.h \
    test_map.h
