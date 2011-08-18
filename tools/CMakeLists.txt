project(tools)

include_directories(${CMAKE_SOURCE_DIR}/src/core ${CMAKE_SOURCE_DIR}/src/core/unix ${CMAKE_SOURCE_DIR}/src/core/windows)

set(D ${CMAKE_SOURCE_DIR}/src)

set(FONTCONV_SRCS
	${D}/fontconv/fontconv.cpp
)

add_executable(fontconv ${FONTCONV_SRCS})
target_link_libraries(fontconv ${HGE_LIBRARY})

set(FONTED_SRCS
	${D}/fonted/commands.cpp
	${D}/fonted/fonted.cpp
	${D}/fonted/fontlist.cpp
	${D}/fonted/generate.cpp
	${D}/fonted/hgeguirange.cpp
	${D}/fonted/savepng.cpp
)

add_executable(fonted ${FONTED_SRCS})
target_link_libraries(fonted ${HGE_HELPER_LIBRARY})

set(PARTICLEED_SRCS
	${D}/particleed/commands.cpp
	${D}/particleed/particleed.cpp
)

add_executable(particleed ${PARTICLEED_SRCS})
target_link_libraries(particleed ${HGE_HELPER_LIBRARY})

set(PNGOPT_SRCS
	${D}/pngopt/pngopt.cpp
	${D}/pngopt/savepngpitch.cpp
)

add_executable(pngopt ${PNGOPT_SRCS})
target_link_libraries(pngopt ${HGE_LIBRARY})

set(TEXASM_SRCS
	${D}/texasm/RectPlacement.cpp
	${D}/texasm/optimized_texture.cpp
	${D}/texasm/sprite_object.cpp
	${D}/texasm/texasm.cpp
	${D}/texasm/texture_assembler.cpp
	${D}/texasm/writePNG.cpp
)

add_executable(texasm ${TEXASM_SRCS})
target_link_libraries(texasm ${HGE_HELPER_LIBRARY})
