QT -= core \
    gui
TARGET = tokenizer
TEMPLATE = lib
CONFIG += staticlib
HEADERS += token.h \
    tokenizer.h \
    unicodesource.h \
    unicodeistreamwrapper.h \
    unicodeicustringwrapper.h \
    tokenlayer.h \
    token_layers/outputqueuelayer.h \
    token_layers/basicsplitlayer.h \
    token_layers/combinelayer.h \
    tokensource.h \
    whitespacetokenizer.h \
    config.h \
    token_layers/inputbufferlayer.h \
    token_layers/appendlayer.h \
    tokenizerconfig.h \
    layertokenizer.h \
    nullunicodesource.h \
    token_layers/affixsplitlayer.h \
    token_layers/regexpclassifylayer.h \
    token_layers/inittokenlayers.h
SOURCES += token.cpp \
    tokenizer.cpp \
    unicodesource.cpp \
    unicodeistreamwrapper.cpp \
    unicodeicustringwrapper.cpp \
    tokenlayer.cpp \
    token_layers/outputqueuelayer.cpp \
    token_layers/basicsplitlayer.cpp \
    token_layers/combinelayer.cpp \
    tokensource.cpp \
    whitespacetokenizer.cpp \
    config.cpp \
    token_layers/inputbufferlayer.cpp \
    token_layers/appendlayer.cpp \
    tokenizerconfig.cpp \
    layertokenizer.cpp \
    nullunicodesource.cpp \
    token_layers/affixsplitlayer.cpp \
    token_layers/regexpclassifylayer.cpp \
    token_layers/inittokenlayers.cpp
LIBS += -licuuc \
    -licuio \
    -lboost_program_options
CONFIG += link_pkgconfig
PKGCONFIG += libxml++-2.6
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/lib
QMAKE_CXXFLAGS += -static
