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
    hs_concepts.cpp \
    dommodel.cpp \
    str_enum.cpp

HEADERS  += mainwindow.h \
    hs_concepts.h \
    dommodel.h \
    str_enum.h

FORMS    +=

OTHER_FILES += \
    resources/test.xml \
    resources/cards.xml \
    resources/tokens.xml
