
PROJECT( test )

include_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

add_definitions(-DLIBTOKI_TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/")


link_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

add_executable( tests main.cpp whitespace.cpp compare.cpp conf.cpp )

target_link_libraries ( tests toki ${Boost_LIBRARIES} icuuc icuio loki) 

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})
include_directories(${ICU_INCLUDE_DIR})
link_directories(${ICU_LIBRARY_DIRS})

SET(CTEST_OUTPUT_ON_FAILURE, 1)
ADD_TEST( tests ${EXECUTABLE_OUTPUT_PATH}/tests )
set_tests_properties(tests PROPERTIES ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1")

