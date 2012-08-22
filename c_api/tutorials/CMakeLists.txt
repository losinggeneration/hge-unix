project(c_tutorials)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/core ${CMAKE_SOURCE_DIR}/src/core/unix ${CMAKE_SOURCE_DIR}/src/core/windows)

set(TUTORIAL01_SRCS
        tutorial01/hge_tut01.c
)

add_executable(hge_c_tut01 ${TUTORIAL01_SRCS})
target_link_libraries(hge_c_tut01 hge_c)

#---------------------------------------------

set(TUTORIAL02_SRCS
        tutorial02/hge_tut02.c
)

add_executable(hge_c_tut02 ${TUTORIAL02_SRCS})
target_link_libraries(hge_c_tut02 hge_c)

#---------------------------------------------
if(BUILD_C_HELPERS_API)
set(TUTORIAL03_SRCS
        tutorial03/hge_tut03.c
)

add_executable(hge_c_tut03 ${TUTORIAL03_SRCS})
target_link_libraries(hge_c_tut03 hge hge_c)

#---------------------------------------------

set(TUTORIAL04_SRCS
        tutorial04/hge_tut04.c
)

add_executable(hge_c_tut04 ${TUTORIAL04_SRCS})
target_link_libraries(hge_c_tut04 hge_c)

#---------------------------------------------

set(TUTORIAL05_SRCS
        tutorial05/hge_tut05.c
)

add_executable(hge_c_tut05 ${TUTORIAL05_SRCS})
target_link_libraries(hge_c_tut05 hge_c m)

#---------------------------------------------

# Partially working
# set(TUTORIAL06_SRCS
#         tutorial06/hge_tut06.c
#         tutorial06/menuitem.c
# )
#
# add_executable(hge_c_tut06 ${TUTORIAL06_SRCS})
# target_link_libraries(hge_c_tut06 hge_c m)

#---------------------------------------------

set(TUTORIAL07_SRCS
        tutorial07/hge_tut07.c
)

add_executable(hge_c_tut07 ${TUTORIAL07_SRCS})
target_link_libraries(hge_c_tut07 hge_c)

#---------------------------------------------

# set(TUTORIAL08_SRCS
#         tutorial08/hge_tut08.c
# )
#
# add_executable(hge_c_tut08 ${TUTORIAL08_SRCS})
# target_link_libraries(hge_c_tut08 hge_c)

endif(BUILD_C_HELPERS_API)
