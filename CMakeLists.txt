project(hge_unix)
cmake_minimum_required(VERSION 2.8)

option(BUILD_TUTORIALS "Build the tutorial samples" OFF)
option(BUILD_TOOLS "Build the library tools" OFF)

if(UNIX OR APPLE)
	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
	option(USE_CXIMAGE "Use CXImage (no)" ON)

	find_package(SDL REQUIRED)
	find_package(OpenAL REQUIRED)
	find_package(Vorbis REQUIRED)
	find_package(ZLIB REQUIRED)
	find_package(JPEG REQUIRED)

	if(USE_CXIMAGE)
		add_definitions(-DSUPPORT_CXIMAGE)
	else(USE_CXIMAGE)
		find_package(DevIL REQUIRED)
		message(ERROR "DevIL is not ready to be used yet")
	endif(USE_CXIMAGE)

	include_directories(
		${SDL_INCLUDE_DIR}
		${OPENAL_INCLUDE_DIR}
		${VORBIS_INCLUDE_DIR}
		${IL_INCLUDE_DIR}
		${ZLIB_INCLUDE_DIR}
		${JPEG_INCLUD_DIR}
		${CMAKE_SOURCE_DIR}/include
# 		${CMAKE_SOURCE_DIR}/include/png
		${CMAKE_SOURCE_DIR}/core
	)

	add_definitions(-DPLATFORM_UNIX -D_LINUX)
	if(APPLE)
		add_definitions(-DPLATFORM_MACOSX)
	endif(APPLE)


	set(HGE_LIBRARY
		${SDL_LIBRARY}
		${OPENAL_LIBRARY}
		${VORBISFILE_LIBRARY}
		${IL_LIBRARIES}
		${ILU_LIBRARIES}
		${ZLIB_LIBRARY}
		${JPEG_LIBRARY}
	)
endif(UNIX OR APPLE)

add_subdirectory(src/core)

if(BUILD_TUTORIALS)
add_subdirectory(tutorials)
endif(BUILD_TUTORIALS)

if(BUILD_TOOLS)
if(UNIX OR APPLE)
	message(ERROR "Tools currently broken for your platform")
endif(UNIX OR APPLE)
add_subdirectory(tools)
endif(BUILD_TOOLS)