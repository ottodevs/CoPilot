#-------------------------------------------------
#
# Project created by QtCreator 2014-01-28T17:29:39
#
#-------------------------------------------------

QT       += core gui xml widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = CoPilot
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dommodel.cpp \
    str_enum.cpp \
    hs/engine.cpp \
    hs/concepts.cpp \
    hs/events.cpp

HEADERS  += mainwindow.h \
    dommodel.h \
    str_enum.h \
    hs/engine.h \
    hs/concepts.h \
    hs/events.h

FORMS    +=

OTHER_FILES += \
    resources/cards.xml \
    resources/tokens.xml
