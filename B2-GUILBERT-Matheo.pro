TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.cpp \
        main.cpp \
        scenario.cpp \
        tests.cpp

HEADERS += \
    functions.h \
    scenario.h \
    tests.h \
    typeDef.h
