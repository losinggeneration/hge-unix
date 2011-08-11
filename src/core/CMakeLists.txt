project(hge)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HGE_SRCS
	demo.cpp
	random.cpp
	timer.cpp

	# ZLib
	ZLIB/unzip.c
	ZLIB/ioapi.c
)

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
if(UNIX OR APPLE)
	set(HGE_SRCS
		${HGE_SRCS}
		graphics_unix.cpp
		ini_unix.cpp
		input_unix.cpp
		power_unix.cpp
		resource_unix.cpp
		sound_openal.cpp
		system_unix.cpp
	)
else(UNIX OR APPLE)
	set(HGE_SRCS
		${HGE_SRCS}
		graphics.cpp
		ini.cpp
		input.cpp
		power.cpp
		resource.cpp
		sound_libbass.cpp
		system.cpp
	)
endif(UNIX OR APPLE)

add_library(hge SHARED ${HGE_SRCS})
target_link_libraries(hge ${HGE_LIBRARY})

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

add_library(hge_helpers SHARED ${HGE_HELPER_SRCS})
target_link_libraries(hge_helpers hge ${HGE_LIBRARY})
