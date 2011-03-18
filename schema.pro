QT += xmlpatterns
FORMS += schema.ui
HEADERS = mainwindow.h \
    xmlsyntaxhighlighter.h
RESOURCES = schema.qrc
SOURCES = main.cpp \
    mainwindow.cpp \
    xmlsyntaxhighlighter.cpp
TRANSLATIONS = shema_ru.ts
CODECFORSRC     = UTF-8
win32 {
    QMAKE_LFLAGS += -static-libgcc
}

