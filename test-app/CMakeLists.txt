include_directories( ${CMAKE_SOURCE_DIR}/tokenizer/ )

link_directories( ${CMAKE_SOURCE_DIR}/tokenizer/ )

add_executable( test-app main.cpp )

target_link_libraries ( test-app tokenizer ${Boost_LIBRARIES} icuuc icuio loki) 

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
