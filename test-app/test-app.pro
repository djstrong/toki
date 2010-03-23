# -------------------------------------------------
# Project created by QtCreator 2010-03-23T11:17:14
# -------------------------------------------------
QT -= core \
    gui
TARGET = test-app
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
INCLUDEPATH += ../tokenizer/
LIBS += ../tokenizer/libtokenizer.a
LIBS += -licuuc \
    -licuio \
    -lloki \
    -lboost_program_options
PRE_TARGETDEPS += ../tokenizer/libtokenizer.a
HEADERS += 
