# -------------------------------------------------
# Project created by QtCreator 2010-03-23T11:17:14
# -------------------------------------------------
QT -= core \
    gui
TARGET = toki-app
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
INCLUDEPATH += ../libtoki/
LIBS += ../libtoki/libtoki.a
LIBS += -licuuc \
    -licuio \
    -lloki \
    -lboost_program_options \
    -lboost_filesystem
PRE_TARGETDEPS += ../libtoki/libtoki.a
HEADERS += 
