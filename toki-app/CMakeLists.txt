PROJECT(toki-app)

include_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )
link_directories( ${CMAKE_SOURCE_DIR}/libtoki/ )

add_executable( toki-app main.cpp )

target_link_libraries ( toki-app toki ${Boost_LIBRARIES})

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

if(UNIX)

        install(TARGETS toki-app
                RUNTIME DESTINATION bin)
        
endif(UNIX)
