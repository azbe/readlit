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
    cpp/Author.cpp \
    cpp/Book.cpp \
    cpp/BrowserButton.cpp \
    cpp/DataButton.cpp \
    cpp/DataList.cpp \
    cpp/DataTable.cpp \
    cpp/main.cpp \
    cpp/MainWindow.cpp \
    cpp/ScannerButton.cpp \
    cpp/SubtabAuthors.cpp \
    cpp/SubtabBooks.cpp

HEADERS  += \
    src/Author.h \
    src/Book.h \
    src/BrowserButton.h \
    src/Constants.h \
    src/DataButton.h \
    src/DataList.h \
    src/DataTable.h \
    src/MainWindow.h \
    src/ScannerButton.h \
    src/SubtabAuthors.h \
    src/SubtabBooks.h

FORMS    += widget.ui
