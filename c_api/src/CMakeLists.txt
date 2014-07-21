if(NOT USE_SHARED)
	message(FATAL_ERROR "C library can only be built as a shared library")
endif(NOT USE_SHARED)

set(HGE_C_SRCS
	hge.cpp
)

if(BUILD_C_HELPERS_API)
	set(HGE_C_HELPER_SRCS
		hgeanim.cpp
		hgecolor.cpp
		hgedistort.cpp
		hgefont.cpp
		hgegui.cpp
		hgeguictrls.cpp
		hgeparticle.cpp
		hgerect.cpp
		hgeresource.cpp
		hgesprite.cpp
		hgestrings.cpp
		hgevector.cpp
	)
endif(BUILD_C_HELPERS_API)

if(LUA_SCRIPTING)
	set(HGE_LUA_SRCS
		lua/hge.c
	)

	if(BUILD_C_HELPERS_API)
		list(APPEND HGE_LUA_SRCS
			lua/hgecolor.c
			lua/hgedistort.c
			lua/hgefont.c
			lua/hgegui.c
			lua/hgeparticle.c
			lua/hgerect.c
			lua/hgeresource.c
			lua/hgesprite.c
			lua/hgestrings.c
			lua/hgevector.c
		)
	endif(BUILD_C_HELPERS_API)
endif(LUA_SCRIPTING)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/core ${CMAKE_SOURCE_DIR}/src/core/unix ${CMAKE_SOURCE_DIR}/src/core/windows)

if(WIN32 OR ${BUILD_SINGLE_LIB})
	add_library(hge_c ${USE_SHARED} ${HGE_C_SRCS} ${HGE_C_HELPER_SRCS} ${HGE_LUA_SRCS})
	target_link_libraries(hge_c hge)
	set(HGE_C_TARGETS hge_c)
else()
	message(FATAL_ERROR "Not Implemented yet")
	add_library(hge_c ${USE_SHARED} ${HGE_C_SRCS})
	target_link_libraries(hge_c hge)

	add_library(hge_c_helpers ${USE_SHARED} ${HGE_C_HELPER_SRCS})
	target_link_libraries(hge_c_helpers hge_c)
	set(HGE_C_TARGETS hge_c hge_helpers_c)
endif()

install(TARGETS ${HGE_C_TARGETS}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

if(BUILD_C_HELPERS_API)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/c_api/include/
	DESTINATION include/hge/c
	FILES_MATCHING PATTERN "*.h"
)
else(BUILD_C_HELPERS_API)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/c_api/include/
	DESTINATION include/hge/c
	FILES_MATCHING PATTERN "hge_c.h"
)
endif(BUILD_C_HELPERS_API)
