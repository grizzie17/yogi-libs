cmake_minimum_required(VERSION 3.15.0)
project(YogiLibs
		VERSION 0.1.0
		LANGUAGES CXX)

# include(cmake/StandardProjectSettings.cmake)
include(cmake-config/StandardProjectSettings.cmake)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
	message(FATAL_ERROR "In-Source builds not allowed. Please run CMake from a 'build' directory.")
endif()


set(CMAKE_CXX_STANDARD 17)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

include_directories(math)

add_subdirectory(math)


# test
add_subdirectory(googletest)


if ( CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-D_DEBUG=1)
	add_definitions(-DDEBUG=1)
else()
	add_definitions(-DNDEBUG=1)
endif()
