project(hge_unix)
cmake_minimum_required(VERSION 2.8)

option(BUILD_TUTORIALS "Build the tutorial samples" OFF)
option(BUILD_TOOLS "Build the library tools" OFF)
option(USE_INTERNAL_ZLIB "Use the internal ZLib" OFF)
option(ENABLE_SCRIPTING_LUA "Enables Lua scripting" ON)

if(ENABLE_SCRIPTING_LUA)
	option(USE_LUNA_GEN "Use luna-gen to for Lua bingings" OFF)
endif()

if(UNIX OR APPLE)
	# Needed for FindVorbis
	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

	# Add our option  for using CxImage,  default is on
	option(USE_CXIMAGE "Use CXImage (no)" ON)

	find_package(SDL REQUIRED)
	find_package(OpenAL REQUIRED)
	find_package(Vorbis REQUIRED)
	find_package(JPEG REQUIRED)
	find_package(PNG REQUIRED)

	# If we're using the external library, we must find it
	if(NOT USE_INTERNAL_ZLIB)
		find_package(ZLIB REQUIRED)
	endif(NOT USE_INTERNAL_ZLIB)

	if(USE_CXIMAGE)
		# CxImage required defines
		add_definitions(-DSUPPORT_CXIMAGE)
	else(USE_CXIMAGE)
		# If we're not using CxImage, we'll use this, more common external library
		find_package(DevIL REQUIRED)
		# Unfortunately though, it's not implemented/working ;)
		message(FATAL_ERROR "DevIL is not ready to be used yet")
	endif(USE_CXIMAGE)

	include_directories(
		${SDL_INCLUDE_DIR}
		${OPENAL_INCLUDE_DIR}
		${VORBIS_INCLUDE_DIR}
		${IL_INCLUDE_DIR}
		${ZLIB_INCLUDE_DIR}
		${JPEG_INCLUDE_DIR}
		${PNG_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_SOURCE_DIR}/core
	)

	add_definitions(-D_LINUX)

	# The libraries to link against for HGE, and also for applications using it
	set(HGE_LIBRARIES
		${SDL_LIBRARY}
		${OPENAL_LIBRARY}
		${VORBISFILE_LIBRARY}
		${IL_LIBRARIES}
		${ILU_LIBRARIES}
		${ZLIB_LIBRARY}
		${JPEG_LIBRARY}
		${PNG_LIBRARY}
	)
endif(UNIX OR APPLE)

if(ENABLE_SCRIPTING_LUA)
	if(USE_LUNA_GEN)
		set(HGE_BINDING_LUA hgeBindingLua)
	else()
		find_package(OOLua REQUIRED)
		set(HGE_BINDING_LUA oolua_hge)
	endif()

	set(HGE_LIBRARIES
		${HGE_LIBRARIES}
		${HGE_BINDING_LUA}
	)
endif(ENABLE_SCRIPTING_LUA)

# This is the HGE library and required libraries to link against
set(HGE_LIBRARY hge ${HGE_LIBRARIES})
# And this is the HGE & Helper library and required libraries to link against
set(HGE_HELPER_LIBRARY hge_helpers ${HGE_LIBRARY})

# Where HGE is located, this also builds the helper library
add_subdirectory(src/core)

if(ENABLE_SCRIPTING_LUA)
	add_subdirectory(src/core/scripting/lua)
endif(ENABLE_SCRIPTING_LUA)

# Did tutorials get enabled to be built?
if(BUILD_TUTORIALS)
	add_subdirectory(tutorials)
endif(BUILD_TUTORIALS)

# Are we building the tools?
if(BUILD_TOOLS)
	add_subdirectory(tools)
endif(BUILD_TOOLS)
