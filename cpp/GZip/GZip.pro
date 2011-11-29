QT -= core gui

TARGET = GZip
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    zutil.c \
    uncompr.c \
    trees.c \
    infutil.c \
    inftrees.c \
    inflate.c \
    inffast.c \
    infcodes.c \
    infblock.c \
    gzio.c \
    deflate.c \
    crc32.c \
    compress.c \
    adler32.c \
    gzstream.cpp

HEADERS += \
    zutil.h \
    zlib.h \
    zconf.h \
    trees.h \
    infutil.h \
    inftrees.h \
    inffixed.h \
    inffast.h \
    infcodes.h \
    infblock.h \
    deflate.h \
    gzstream.h








