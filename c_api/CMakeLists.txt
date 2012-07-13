include_directories(include)
add_subdirectory(src)

if(BUILD_C_TUTORIALS)
	add_subdirectory(tutorials)
endif(BUILD_C_TUTORIALS)