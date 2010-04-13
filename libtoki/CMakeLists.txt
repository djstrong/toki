########## libtokenizer ###############

include_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

set(LIBTOKI_INSTALL_DATA_DIR lib/toki/)

add_definitions(-DLIBTOKI_DATA_DIR="${CMAKE_INSTALL_PREFIX}/${LIBTOKI_INSTALL_DATA_DIR}")

FIND_PATH(LIBTOKI_SRC_DATA_DIR
	config.ini
	${CMAKE_SOURCE_DIR}/config
)
MARK_AS_ADVANCED(LIBTOKI_SRC_DATA_DIR)

if(NOT LIBTOKI_SRC_DATA_DIR)
	message(FATAL_ERROR "There is no data for libtoki")
endif(NOT LIBTOKI_SRC_DATA_DIR)
SET(libtoki_STAT_SRC
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

add_library(toki STATIC ${libtoki_STAT_SRC})

if(UNIX)
        install(TARGETS toki
                ARCHIVE DESTINATION lib)
        
        install(
                DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                DESTINATION include
                FILES_MATCHING PATTERN "*.h"
                PATTERN ".svn" EXCLUDE
                PATTERN "bin" EXCLUDE
                PATTERN "build" EXCLUDE 
                PATTERN "CMake*" EXCLUDE
        )
        
        install(
                DIRECTORY ${LIBTOKI_SRC_DATA_DIR}/
                DESTINATION ${LIBTOKI_INSTALL_DATA_DIR}
                FILES_MATCHING PATTERN "*.ini"
                PATTERN ".svn" EXCLUDE
        )
endif(UNIX)

