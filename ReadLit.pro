
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReadLit
TEMPLATE = app
CONFIG += c++11

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
    cpp/SubtabBooks.cpp \
    cpp/Reader.cpp \
    cpp/ImageLoader.cpp \
    cpp/Database.cpp \
    cpp/Settings.cpp

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
    src/SubtabBooks.h \
    src/Reader.h \
    src/ImageLoader.h \
    src/Database.h \
    src/Settings.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lpoppler-qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lpoppler-qt5
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lpoppler-qt5

INCLUDEPATH += $$PWD/../../../../usr/include/poppler/qt5
DEPENDPATH += $$PWD/../../../../usr/include/poppler/qt5

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/libpoppler-qt5.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/libpoppler-qt5.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/poppler-qt5.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/poppler-qt5.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/libpoppler-qt5.a
