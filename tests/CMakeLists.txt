PROJECT( test )

include_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

add_definitions(-DLIBTOKI_TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/")

link_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

add_executable( tests main.cpp whitespace.cpp compare.cpp conf.cpp )

target_link_libraries ( tests toki ${Boost_LIBRARIES})

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_custom_target(test tests)
