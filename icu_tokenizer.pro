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
    token_layers/appendlayer.h
SOURCES += token.cpp \
    main.cpp \
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
    token_layers/appendlayer.cpp
LIBS += -licuuc \
    -licuio \
    -lloki \
    -lboost_program_options \
    -lclaw_configuration_file
CONFIG += link_pkgconfig
PKGCONFIG += libxml++-2.6
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/lib
