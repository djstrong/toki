# -------------------------------------------------
# Project created by QtCreator 2010-03-23T15:11:17
# -------------------------------------------------
QT -= core \
    gui
TARGET = unit_tests
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    whitespace.cpp \
    compare.cpp
INCLUDEPATH += ../tokenizer/
LIBS += ../tokenizer/libtokenizer.a
LIBS += -licuuc \
    -licuio \
    -lloki \
    -lboost_program_options \
    -lboost_filesystem
PRE_TARGETDEPS += ../tokenizer/libtokenizer.a
HEADERS += compare.h
