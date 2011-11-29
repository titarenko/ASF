QT += core gui

TARGET = AsfViewer
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS += MainWindow.h

FORMS += MainWindow.ui

debug {
    LIBS += ../AsfLibrary/debug/libAsf.a
    LIBS += ../GZip/debug/libGZip.a
}

release {
    LIBS += ../AsfLibrary/release/libAsf.a
    LIBS += ../GZip/release/libGZip.a
}

INCLUDEPATH += ../AsfLibrary \
    ../GZip

RESOURCES += resources.qrc
