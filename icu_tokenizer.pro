HEADERS += token.h \
    tokenizer.h \
    unicodesource.h \
    icustreamwrapper.h \
    icustringsource.h \
    tokenlayer.h \
    queuetokenlayer.h \
    tokenlayerfactory.h \
    basicsplitlayer.h \
    combinelayer.h
SOURCES += token.cpp \
    main.cpp \
    tokenizer.cpp \
    unicodesource.cpp \
    icustreamwrapper.cpp \
    icustringsource.cpp \
    tokenlayer.cpp \
    queuetokenlayer.cpp \
    basicsplitlayer.cpp \
    combinelayer.cpp
LIBS += -licuuc \
    -licuio \
    -lloki \
    -lboost_program_options-mt
