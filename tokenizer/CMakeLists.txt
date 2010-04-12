########## libtokenizer ###############

include_directories( ${CMAKE_SOURCE_DIR}/tokenizer/ )

SET(libtokenizer_STAT_SRC
    config.cpp
    debug.cpp
    layertokenizer.cpp
    nullunicodesource.cpp
    token.cpp
    tokenizer.cpp
    tokenlayer.cpp
    token_layers/affixsplitlayer.cpp
    token_layers/appendlayer.cpp
    token_layers/basicsplitlayer.cpp
    token_layers/combinelayer.cpp
    token_layers/groupsplitlayer.cpp
    token_layers/inittokenlayers.cpp
    token_layers/inputbufferlayer.cpp
    token_layers/lexiconclassifylayer.cpp
    token_layers/outputqueuelayer.cpp
    token_layers/regexpclassifylayer.cpp
    tokensource.cpp
    unicodeicustringwrapper.cpp
    unicodeistreamwrapper.cpp
    unicodesource.cpp
    util.cpp
    whitespacetokenizer.cpp
)

add_library(tokenizer STATIC EXCLUDE_FROM_ALL ${libtokenizer_STAT_SRC})
