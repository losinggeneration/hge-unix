project(hge)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Common source
set(HGE_SRCS
	common/demo.cpp
	common/random.cpp
	common/timer.cpp
)

# Zlib source: internally included or an external library
if(USE_INTERNAL_ZLIB)
	set(HGE_SRCS
		${HGE_SRCS}
		ZLIB/adler32.c
		ZLIB/crc32.c
		ZLIB/inffast.c
		ZLIB/inflate.c
		ZLIB/inftrees.c
		ZLIB/ioapi.c
		ZLIB/trees.c
		ZLIB/uncompr.c
		ZLIB/unzip.c
		ZLIB/zutil.c
	)
else(USE_INTERNAL_ZLIB)
	set(HGE_SRCS
		${HGE_SRCS}
		# AFAICT not part of zlib proper
		ZLIB/ioapi.c
		ZLIB/unzip.c
	)
endif(USE_INTERNAL_ZLIB)

# Are we using CxImage?
if(USE_CXIMAGE)
	set(HGE_SRCS
		${HGE_SRCS}
		# CxImage
		CxImage/tif_xfile.cpp
		CxImage/ximabmp.cpp
		CxImage/ximadsp.cpp
		CxImage/ximaenc.cpp
		CxImage/ximaexif.cpp
		CxImage/ximage.cpp
		CxImage/ximagif.cpp
		CxImage/ximahist.cpp
		CxImage/ximaico.cpp
		CxImage/ximainfo.cpp
		CxImage/ximaint.cpp
		CxImage/ximajas.cpp
		CxImage/ximajbg.cpp
		CxImage/ximajpg.cpp
		CxImage/ximalpha.cpp
		CxImage/ximalyr.cpp
		CxImage/ximamng.cpp
		CxImage/ximapal.cpp
		CxImage/ximapcx.cpp
		CxImage/ximapng.cpp
		CxImage/ximapsd.cpp
		CxImage/ximaraw.cpp
		CxImage/ximasel.cpp
		CxImage/ximaska.cpp
		CxImage/ximatga.cpp
		CxImage/ximath.cpp
		CxImage/ximatif.cpp
		CxImage/ximatran.cpp
		CxImage/ximawbmp.cpp
		CxImage/ximawmf.cpp
		CxImage/ximawnd.cpp
		CxImage/xmemfile.cpp
	)
endif(USE_CXIMAGE)

# Platform specifc files
if(UNIX OR APPLE)
	# Unix/Linux and OS X share these
	include_directories(unix)
	set(HGE_SRCS
		${HGE_SRCS}
		unix/graphics.cpp
		unix/ini.cpp
		unix/input.cpp
		unix/power.cpp
		unix/resource.cpp
		unix/sound_openal.cpp
		unix/system.cpp
	)

	if(APPLE)
		set(HGE_SRCS
			${HGE_SRCS}
			unix/macosx_support.mm
		)
	endif(APPLE)
else(UNIX OR APPLE)
	# Win32, though it's probably broken to build
	include_directories(windows unix)
	set(HGE_SRCS
		${HGE_SRCS}
		windows/graphics.cpp
		windows/ini.cpp
		windows/input.cpp
		windows/power.cpp
		windows/resource.cpp
		windows/sound_libbass.cpp
		windows/system.cpp
	)
endif(UNIX OR APPLE)

set(HS ${CMAKE_SOURCE_DIR}/src/helpers)
set(HGE_HELPER_SRCS
	${HS}/hgeanim.cpp
	${HS}/hgecolor.cpp
	${HS}/hgedistort.cpp
	${HS}/hgefont.cpp
	${HS}/hgegui.cpp
	${HS}/hgeguictrls.cpp
	${HS}/hgeparticle.cpp
	${HS}/hgepmanager.cpp
	${HS}/hgerect.cpp
	${HS}/hgeresource.cpp
	${HS}/hgesprite.cpp
	${HS}/hgestrings.cpp
	${HS}/hgevector.cpp
	${HS}/parser.cpp
	${HS}/resources.cpp
)

if(WIN32)
	add_library(hge ${USE_SHARED} ${HGE_SRCS} ${HGE_HELPER_SRCS})
	target_link_libraries(hge ${HGE_LIBRARIES})
else()
	add_library(hge ${USE_SHARED} ${HGE_SRCS})
	target_link_libraries(hge ${HGE_LIBRARIES})

	add_library(hge_helpers ${USE_SHARED} ${HGE_HELPER_SRCS})
	target_link_libraries(hge_helpers hge ${HGE_LIBRARIES})
endif()
