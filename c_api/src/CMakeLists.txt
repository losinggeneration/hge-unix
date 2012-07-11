if(NOT USE_SHARED)
	message(FATAL_ERROR "C library can only be built as a shared library")
endif(NOT USE_SHARED)

set(HGE_C_SRCS
	hge.cpp
)

set(HGE_C_HELPER_SRCS
	hgeanim.cpp
# 	hgecolor.cpp
	hgedistort.cpp
	hgefont.cpp
# 	hgegui.cpp
# 	hgeguictrls.cpp
# 	hgeparticle.cpp
	hgerect.cpp
# 	hgeresource.cpp
	hgesprite.cpp
	hgestrings.cpp
	hgevector.cpp
)

if(WIN32 OR ${BUILD_SINGLE_LIB})
	add_library(hge_c ${USE_SHARED} ${HGE_C_SRCS} ${HGE_C_HELPER_SRCS})
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

install(TARGETS ${HGE_TARGETS}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/c_api/include/
	DESTINATION include/hge/c
	FILES_MATCHING PATTERN "*.h"
)