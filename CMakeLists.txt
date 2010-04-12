cmake_minimum_required(VERSION 2.6.0)


# use some of our own Find* scripts
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeScripts)


if(CMAKE_COMPILER_IS_GNUCXX)
	# Set our own default flags at first run.
	if(NOT CONFIGURED)

		if(ENABLE_STRICT_COMPILATION)
			set(STRICT_FLAGS "-Werror -Wno-unused-parameter")
		else(ENABLE_STRICT_COMPILATION)
			set(STRICT_FLAGS "")
		endif(ENABLE_STRICT_COMPILATION)


		# Strict compilation for C files is disabled until somebody wants to clean them.
		set(CMAKE_C_FLAGS "-O2 -W -Wall -ansi $ENV{CFLAGS}" 
				CACHE STRING "Flags used by the C compiler during normal builds." FORCE)
		set(CMAKE_C_FLAGS_DEBUG "-O0 -DDEBUG -ggdb3 -W -Wall -ansi $ENV{CFLAGS}"
				CACHE STRING "Flags used by the C compiler during debug builds." FORCE)

		set(CMAKE_CXX_FLAGS "-O2 -W -Wall -ansi ${STRICT_FLAGS} $ENV{CXXFLAGS}"
				CACHE STRING "Flags used by the CXX compiler during normal builds." FORCE)
		set(CMAKE_CXX_FLAGS_DEBUG "-O0 -DDEBUG -ggdb3 -W -Wall -ansi ${STRICT_FLAGS} $ENV{CXXFLAGS}"
				CACHE STRING "Flags used by the CXX compiler during debug builds." FORCE)

	endif(NOT CONFIGURED)

endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(Boost 1.41 REQUIRED COMPONENTS program_options filesystem)

find_package(ICU REQUIRED)

find_package(Loki REQUIRED)

add_subdirectory(libtoki)
add_subdirectory(tests)
add_subdirectory(toki-app)
