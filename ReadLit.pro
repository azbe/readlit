#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T19:04:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReadLit
TEMPLATE = app


SOURCES += \
    Author.cpp \
    Book.cpp \
    BrowserButton.cpp \
    DataButton.cpp \
    DataList.cpp \
    DataTable.cpp \
    main.cpp \
    MainWindow.cpp \
    ScannerButton.cpp \
    SubtabAuthors.cpp \
    SubtabBooks.cpp

HEADERS  += \
    Author.h \
    Book.h \
    BrowserButton.h \
    Constants.h \
    DataButton.h \
    DataList.h \
    DataTable.h \
    MainWindow.h \
    resource.h \
    ScannerButton.h \
    SubtabAuthors.h \
    SubtabBooks.h

FORMS    += widget.ui
