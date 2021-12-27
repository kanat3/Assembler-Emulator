QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        texteditor.cpp\
        Lab4/assembler.cpp\
        Lab4/file_access.cpp\
        Lab4/map.cpp\
        Lab4/operands.cpp

HEADERS += \
        texteditor.h\
        Lab4/assembler.hpp\
        Lab4/file_access.hpp\
        Lab4/operands.hpp\
        Lab4/map.hpp\
        Lab4/tools.hpp

FORMS += \
        texteditor.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

