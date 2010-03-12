HEADERS += token.h \
    tokenizer.h \
    unicodesource.h \
    icustreamwrapper.h \
    icustringsource.h
SOURCES += token.cpp \
    main.cpp \
    tokenizer.cpp \
    unicodesource.cpp \
    icustreamwrapper.cpp \
    icustringsource.cpp
LIBS += -licuuc \
    -licuio \
    -lboost_program_options-mt
