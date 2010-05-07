########## libtokenizer ###############

PROJECT(toki)

set(ver_major "0")
set(ver_minor "2")

set(LIBS "")

find_package(ICU REQUIRED)
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
set(LIBS ${LIBS} icuuc icuio)

find_package(Loki REQUIRED)
set(LIBS ${LIBS} loki)

find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
link_directories(${LibXML++_LIBRARY_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

link_directories(${Boost_LIBRARY_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

include_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

set(LIBTOKI_INSTALL_DATA_DIR lib/toki)
set(LIBTOKI_DATA_DIR "${CMAKE_INSTALL_PREFIX}/${LIBTOKI_INSTALL_DATA_DIR};.")
set(LIBTOKI_VERSION "${ver_major}.${ver_minor}")

FIND_PATH(LIBTOKI_SRC_DATA_DIR
    config.ini
    ${CMAKE_SOURCE_DIR}/config
)
MARK_AS_ADVANCED(LIBTOKI_SRC_DATA_DIR)

if(NOT LIBTOKI_SRC_DATA_DIR)
    message(FATAL_ERROR "There is no data for libtoki")
endif(NOT LIBTOKI_SRC_DATA_DIR)

configure_file(config_d.in include/config_d.h)
include_directories( ${CMAKE_CURRENT_BINARY_DIR}/include/ )
add_definitions(-DHAVE_CONFIG_D_H)

SET(libtoki_STAT_SRC
    config.cpp
    debug.cpp
    layertokenizer.cpp
    main.cpp
    nullunicodesource.cpp
    token.cpp
    tokenizer.cpp
    tokenlayer.cpp
    srx/document.cpp
    srx/processor.cpp
    srx/rule.cpp
    srx/srx.cpp
    srx/util.cpp
    token_layers/affixsplitlayer.cpp
    token_layers/appendlayer.cpp
    token_layers/basicsplitlayer.cpp
    token_layers/checklayer.cpp
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

add_library(toki SHARED ${libtoki_STAT_SRC})
target_link_libraries ( toki ${LIBS} )
set_target_properties(toki PROPERTIES
        VERSION "${ver_major}.${ver_minor}"
        SOVERSION ${ver_major})

if(UNIX)
    set_target_properties(toki PROPERTIES
        LINK_FLAGS -Wl,-e,LIBTOKI_entry_)
endif(UNIX)


if(UNIX)
        install(TARGETS toki
                LIBRARY DESTINATION lib
                PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

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

