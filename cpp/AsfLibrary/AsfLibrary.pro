QT -= core gui

TARGET = Asf
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    AsfFrame.cpp \
    AsfFile.cpp

HEADERS += \
    Exception.h \
    AsfFrame.h \
    AsfFile.h \
    csv_istream_iterator.h \
    from_string.h

INCLUDEPATH += ../GZip
