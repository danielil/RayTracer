# Daniel Sebastian Iliescu, http://dansil.net
# MIT License (MIT), http://opensource.org/licenses/MIT

cmake_minimum_required( VERSION 3.8.0 )

project( RayTracer CXX )

# Create the executable given the source directory
set( SOURCE_DIRECTORY source )
set( EXECUTABLE_NAME ${PROJECT_NAME} )
add_executable(
	${EXECUTABLE_NAME}
	${SOURCE_DIRECTORY}/main.cpp
	${SOURCE_DIRECTORY}/utility/implementation/netpbm.cpp
	${SOURCE_DIRECTORY}/raytracer/implementation/output.cpp
	${SOURCE_DIRECTORY}/raytracer/implementation/raytracer.cpp
	${SOURCE_DIRECTORY}/raytracer/implementation/value_mapping.cpp
	${SOURCE_DIRECTORY}/raytracer/implementation/geometry/object/sphere.cpp )

# Include the source headers
set(
	INCLUDE_HEADERS
	${SOURCE_DIRECTORY}/include
	${SOURCE_DIRECTORY}/raytracer/include
	${SOURCE_DIRECTORY}/utility/include )
target_include_directories(
	${EXECUTABLE_NAME}
	PRIVATE
		${INCLUDE_HEADERS} )

# Include the external headers
set( EXTERNAL_HEADERS external )
target_include_directories(
	${EXECUTABLE_NAME}
	PRIVATE
		${EXTERNAL_HEADERS} )

# Enforce C++17 standard and output settings
set_target_properties(
	${EXECUTABLE_NAME}
	PROPERTIES
		CMAKE_CXX_STANDARD 17
		CMAKE_CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Additional compiler options
set( CLANG_GNU_COMPILER_OPTIONS "-Wall" "-Wextra" "-Werror" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" )
set( CLANG_COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
set( GNU_COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
set( MSVC_COMPILER_OPTIONS "/W4" "/WX" "/std:c++latest" )

if ( CMAKE_CXX_COMPILER_ID MATCHES Clang )
	set( COMPILER_OPTIONS ${CLANG_COMPILER_OPTIONS} )
elseif( CMAKE_CXX_COMPILER_ID MATCHES GNU )
	set( COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
elseif( CMAKE_CXX_COMPILER_ID MATCHES MSVC )
	set( COMPILER_OPTIONS ${MSVC_COMPILER_OPTIONS} )
endif()

target_compile_options(
	${EXECUTABLE_NAME}
	PRIVATE
		${COMPILER_OPTIONS} )

# Option to build tests
option( BUILD_TESTS "Build Tests" ON )

if ( BUILD_TESTS )
	set( TEST_EXECUTABLE_NAME ${EXECUTABLE_NAME}Tests )

	add_executable(
		${TEST_EXECUTABLE_NAME}
		${SOURCE_DIRECTORY}/raytracer/tests/tester.cpp )
endif()