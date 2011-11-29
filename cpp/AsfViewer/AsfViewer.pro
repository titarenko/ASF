QT += core gui

TARGET = AsfViewer
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS += MainWindow.h

FORMS += MainWindow.ui

debug {
    LIBS += ../AsfLibrary/debug/libAsf.a
}

release {
    LIBS += ../AsfLibrary/release/libAsf.a
}

INCLUDEPATH += ../AsfLibrary

RESOURCES += resources.qrc
