find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories( ${CMAKE_SOURCE_DIR}/tokenizer/ )

link_directories( ${CMAKE_SOURCE_DIR}/tokenizer/ )

add_executable( unit_tests main.cpp whitespace.cpp compare.cpp )

target_link_libraries ( unit_tests tokenizer ${Boost_LIBRARIES} icuuc icuio loki) 

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
