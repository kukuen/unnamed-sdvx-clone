# All third party libraries
cmake_minimum_required(VERSION 3.4)

add_subdirectory(lua-5.3.5)

#cpr test programs
option(BUILD_CPR_TESTS "Set to ON to build cpr tests." OFF)
if(WIN32)
	option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
	option(CMAKE_USE_WINSSL "enable Windows native SSL/TLS" ON)
elseif(APPLE)
	set(CURL_CA_PATH "none" CACHE STRING "CURL CA Path")
	option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
	option(CMAKE_USE_DARWINSSL "enable MacOS native SSL/TLS" ON)
endif()
set(SSL_ENABLED ON)

add_subdirectory(cpr)
target_include_directories(cpr PUBLIC ${CPR_INCLUDE_DIRS})

#discord example program
option(BUILD_EXAMPLES "Build example apps" OFF)
add_subdirectory(discord-rpc)
target_include_directories(discord-rpc PUBLIC discord-rpc/include)

if(WIN32)
	# Use bundled third party libraries on windows
	add_subdirectory(freetype)
	add_subdirectory(jpeg-9b)
	add_subdirectory(zlib-1.2.8)
	add_subdirectory(SDL2-2.0.9)
	add_subdirectory(lpng1621)
	add_subdirectory(libogg-1.3.2)
	add_subdirectory(libvorbis-1.3.5)
endif(WIN32)

#nanovg
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src)
add_library(nanovg nanovg/src/nanovg.c)
target_include_directories(nanovg PUBLIC nanovg/src)
if(WIN32)
    target_link_libraries(nanovg freetype)
else(WIN32)
	set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/third_party)
	include(FindLibraries)
	target_link_libraries(nanovg ${FREETYPE_LIBRARIES})
	include_directories(${FREETYPE_INCLUDE_DIRS})
	find_package(Freetype REQUIRED)
endif(WIN32)
add_definitions(-DFONS_USE_FREETYPE)

#miniaudio
set_property(GLOBAL PROPERTY MA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio)

#json for modern c++
set_property(GLOBAL PROPERTY NLOHMANN_JSON_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json)

#libarchive
set(ENABLE_TEST OFF CACHE BOOL "Enable unit and regression tests")
set(ENABLE_INSTALL OFF CACHE BOOL "Enable installing of libraries")
set(ENABLE_TAR OFF CACHE BOOL "Enable tar building")
set(ENABLE_CPIO OFF CACHE BOOL "Enable cpio building")
set(ENABLE_CAT OFF CACHE BOOL "Enable cat building")
set(ENABLE_OPENSSL OFF CACHE BOOL "Enable use of OpenSSL")


set(ENABLE_WERROR OFF CACHE BOOL "Treat warnings as errors - default is ON for Debug, OFF otherwise.")
add_subdirectory(libarchive)
target_include_directories(archive PUBLIC libarchive/libarchive)