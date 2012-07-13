project(c_tutorials)

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

# set(TUTORIAL03_SRCS
#         tutorial03/hge_tut03.c
# )
#
# add_executable(hge_c_tut03 ${TUTORIAL03_SRCS})
# target_link_libraries(hge_c_tut03 hge ${HGE_HELPER_LIBRARY})
#
# #---------------------------------------------
#
# set(TUTORIAL04_SRCS
#         tutorial04/hge_tut04.c
# )
#
# add_executable(hge_c_tut04 ${TUTORIAL04_SRCS})
# target_link_libraries(hge_c_tut04 ${HGE_HELPER_LIBRARY})
#
# #---------------------------------------------
#
# set(TUTORIAL05_SRCS
#         tutorial05/hge_tut05.c
# )
#
# add_executable(hge_c_tut05 ${TUTORIAL05_SRCS})
# target_link_libraries(hge_c_tut05 ${HGE_HELPER_LIBRARY})
#
# #---------------------------------------------
#
# set(TUTORIAL06_SRCS
#         tutorial06/hge_tut06.c
#         tutorial06/menuitem.c
# )
#
# add_executable(hge_c_tut06 ${TUTORIAL06_SRCS})
# target_link_libraries(hge_c_tut06 ${HGE_HELPER_LIBRARY})
#
# #---------------------------------------------
#
# set(TUTORIAL07_SRCS
#         tutorial07/hge_tut07.c
# )
#
# add_executable(hge_c_tut07 ${TUTORIAL07_SRCS})
# target_link_libraries(hge_c_tut07 ${HGE_HELPER_LIBRARY})
#
# #---------------------------------------------
#
# set(TUTORIAL08_SRCS
#         tutorial08/hge_tut08.c
# )
#
# add_executable(hge_c_tut08 ${TUTORIAL08_SRCS})
# target_link_libraries(hge_c_tut08 ${HGE_HELPER_LIBRARY})